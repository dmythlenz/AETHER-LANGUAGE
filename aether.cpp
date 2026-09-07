#include "aether/aether.hpp"
#include <cctype>
#include <sstream>
#include <algorithm>

namespace aether {

static Token tok(TokenKind k, std::string t, std::size_t l, std::size_t c){ return {k,std::move(t),l,c}; }

std::vector<Token> lex(std::string_view s){
  std::vector<Token> out; std::size_t i=0,l=1,c=1;
  auto add=[&](TokenKind k,std::size_t sl,std::size_t sc,std::string t){out.push_back(tok(k,std::move(t),sl,sc));};
  while(i<s.size()){
    char ch=s[i];
    if(ch==' '||ch=='\t'||ch=='\r'){++i;++c;continue;}
    if(ch=='\n'){add(TokenKind::Newline,l,c,"\\n");++i;++l;c=1;continue;}
    if(ch=='#'){while(i<s.size()&&s[i]!='\n'){++i;++c;}continue;}
    std::size_t sl=l,sc=c;
    if(std::isalpha((unsigned char)ch)||ch=='_'||ch=='$'){
      std::size_t st=i; while(i<s.size()&&(std::isalnum((unsigned char)s[i])||s[i]=='_'||s[i]=='$')){++i;++c;}
      std::string w(s.substr(st,i-st));
      TokenKind k=TokenKind::Identifier;
      if(w=="let")k=TokenKind::Let; else if(w=="mut")k=TokenKind::Mut; else if(w=="const")k=TokenKind::Const;
      else if(w=="fn")k=TokenKind::Fn; else if(w=="return")k=TokenKind::Return; else if(w=="if")k=TokenKind::If; else if(w=="else")k=TokenKind::Else;
      add(k,sl,sc,std::move(w)); continue;
    }
    if(std::isdigit((unsigned char)ch)){
      std::size_t st=i; bool dot=false; while(i<s.size()&&(std::isdigit((unsigned char)s[i])||(s[i]=='.'&&!dot))){if(s[i]=='.')dot=true;++i;++c;}
      add(TokenKind::Number,sl,sc,std::string(s.substr(st,i-st))); continue;
    }
    if(ch=='"'||ch=='\''){
      char q=ch; ++i;++c; std::string v;
      while(i<s.size()&&s[i]!=q){ if(s[i]=='\\'&&i+1<s.size()){ v+=s[i+1]; i+=2;c+=2; } else {v+=s[i++];++c;} }
      if(i>=s.size()) throw Error("unterminated string",sl,sc); ++i;++c; add(TokenKind::String,sl,sc,std::move(v)); continue;
    }
    auto one=[&](TokenKind k){add(k,sl,sc,std::string(1,ch));++i;++c;};
    if(ch=='('){one(TokenKind::LParen);continue;} if(ch==')'){one(TokenKind::RParen);continue;}
    if(ch=='{'){one(TokenKind::LBrace);continue;} if(ch=='}'){one(TokenKind::RBrace);continue;} if(ch==','){one(TokenKind::Comma);continue;} if(ch==':'){one(TokenKind::Colon);continue;}
    if(ch=='+'){one(TokenKind::Plus);continue;} if(ch=='-'){
      if(i+1<s.size()&&s[i+1]=='>'){add(TokenKind::Arrow,sl,sc,"->");i+=2;c+=2;} else one(TokenKind::Minus); continue;
    }
    if(ch=='*'){one(TokenKind::Star);continue;} if(ch=='/'){one(TokenKind::Slash);continue;}
    if(ch=='='){if(i+1<s.size()&&s[i+1]=='='){add(TokenKind::EqEq,sl,sc,"==");i+=2;c+=2;}else one(TokenKind::Eq);continue;}
    if(ch=='!'){if(i+1<s.size()&&s[i+1]=='='){add(TokenKind::NotEq,sl,sc,"!=");i+=2;c+=2;}else throw Error("unexpected !",sl,sc);continue;}
    if(ch=='<'){if(i+1<s.size()&&s[i+1]=='='){add(TokenKind::LtEq,sl,sc,"<=");i+=2;c+=2;}else one(TokenKind::Lt);continue;}
    if(ch=='>'){if(i+1<s.size()&&s[i+1]=='='){add(TokenKind::GtEq,sl,sc,">=");i+=2;c+=2;}else one(TokenKind::Gt);continue;}
    throw Error(std::string("unexpected character: ")+ch,sl,sc);
  }
  add(TokenKind::End,l,c,""); return out;
}

class Parser{
  const std::vector<Token>& t; std::size_t i=0;
  const Token& peek() const{return t[i];}
  const Token& take(){return t[i++];}
  void skipNL(){while(peek().kind==TokenKind::Newline)++i;}
  void need(TokenKind k,const char* m){if(peek().kind!=k)throw Error(m,peek().line,peek().col);++i;}
  std::unique_ptr<Expr> expr(int minp=0){
    skipNL(); Token x=take(); std::unique_ptr<Expr> e=std::make_unique<Expr>(); e->line=x.line;e->col=x.col;
    if(x.kind==TokenKind::Number||x.kind==TokenKind::String){e->kind=x.kind==TokenKind::Number?Expr::Kind::Number:Expr::Kind::String;e->value=x.text;}
    else if(x.kind==TokenKind::Identifier){
      if(peek().kind==TokenKind::LParen){e->kind=Expr::Kind::Call;e->value=x.text;take();skipNL();if(peek().kind!=TokenKind::RParen){while(true){e->args.push_back(expr());skipNL();if(peek().kind==TokenKind::Comma){take();continue;}break;}}need(TokenKind::RParen,"expected )");}
      else {e->kind=Expr::Kind::Name;e->value=x.text;}
    } else if(x.kind==TokenKind::Minus){e->kind=Expr::Kind::Unary;e->value="-";e->rhs=expr(100);} 
    else if(x.kind==TokenKind::LParen){e=expr();need(TokenKind::RParen,"expected )");}
    else throw Error("expected expression",x.line,x.col);
    auto prec=[](TokenKind k)->int{switch(k){case TokenKind::EqEq:case TokenKind::NotEq: return 10;case TokenKind::Lt:case TokenKind::LtEq:case TokenKind::Gt:case TokenKind::GtEq:return 20;case TokenKind::Plus:case TokenKind::Minus:return 30;case TokenKind::Star:case TokenKind::Slash:return 40;default:return -1;}};
    while(true){skipNL(); int p=prec(peek().kind); if(p<minp)break; Token op=take(); auto r=expr(p+1); auto b=std::make_unique<Expr>();b->kind=Expr::Kind::Binary;b->value=op.text;b->lhs=std::move(e);b->rhs=std::move(r);b->line=op.line;b->col=op.col;e=std::move(b);} return e;
  }
public:
  explicit Parser(const std::vector<Token>&tt):t(tt){}
  Program program(){Program p;skipNL();while(peek().kind!=TokenKind::End){need(TokenKind::Fn,"expected fn");Token n=take();if(n.kind!=TokenKind::Identifier)throw Error("expected function name",n.line,n.col);Function f;f.name=n.text;f.line=n.line;f.col=n.col;need(TokenKind::LParen,"expected (");skipNL();if(peek().kind!=TokenKind::RParen){while(true){Token a=take();if(a.kind!=TokenKind::Identifier)throw Error("expected parameter",a.line,a.col);f.params.push_back(a.text);skipNL();if(peek().kind==TokenKind::Comma){take();continue;}break;}}need(TokenKind::RParen,"expected )");need(TokenKind::Arrow,"expected ->");f.body=expr();skipNL();p.functions.push_back(std::move(f));}return p;}
};
Program parse(const std::vector<Token>&t){return Parser(t).program();}

Value Value::integer(std::int64_t v){Value x;x.i=v;return x;} Value Value::boolean(bool v){Value x;x.kind=Kind::Bool;x.b=v;return x;} Value Value::string(std::string v){Value x;x.kind=Kind::String;x.s=std::move(v);return x;}
const Function* VM::find(std::string_view n) const{for(auto&f:program_.functions)if(f.name==n)return &f;return nullptr;}
Value VM::eval(const Expr&e,const std::unordered_map<std::string,Value>&env) const{
  if(e.kind==Expr::Kind::Number)return Value::integer(std::stoll(e.value));
  if(e.kind==Expr::Kind::String)return Value::string(e.value);
  if(e.kind==Expr::Kind::Name){auto it=env.find(e.value);if(it==env.end())throw Error("unknown name: "+e.value,e.line,e.col);return it->second;}
  if(e.kind==Expr::Kind::Unary){auto v=eval(*e.rhs,env);if(e.value=="-")return Value::integer(-v.i);}
  if(e.kind==Expr::Kind::Call){std::vector<Value>a;for(auto&x:e.args)a.push_back(eval(*x,env));return call(e.value,a);}
  auto a=eval(*e.lhs,env),b=eval(*e.rhs,env);if(a.kind!=Value::Kind::Int||b.kind!=Value::Kind::Int)throw Error("operator requires integers",e.line,e.col);
  if(e.value=="+")return Value::integer(a.i+b.i);if(e.value=="-")return Value::integer(a.i-b.i);if(e.value=="*")return Value::integer(a.i*b.i);if(e.value=="/"){if(!b.i)throw Error("division by zero",e.line,e.col);return Value::integer(a.i/b.i);}if(e.value=="==")return Value::boolean(a.i==b.i);if(e.value=="!=")return Value::boolean(a.i!=b.i);if(e.value=="<")return Value::boolean(a.i<b.i);if(e.value=="<=")return Value::boolean(a.i<=b.i);if(e.value==">")return Value::boolean(a.i>b.i);if(e.value==">=")return Value::boolean(a.i>=b.i);throw Error("unknown operator",e.line,e.col);
}
Value VM::call(std::string_view n,const std::vector<Value>&args) const{const Function*f=find(n);if(!f)throw std::runtime_error("unknown function: "+std::string(n));if(args.size()!=f->params.size())throw std::runtime_error("arity mismatch for "+std::string(n));std::unordered_map<std::string,Value> env;for(size_t i=0;i<args.size();++i)env[f->params[i]]=args[i];return eval(*f->body,env);}

static void wat_expr(const Expr&e,std::ostringstream&o){
  if(e.kind==Expr::Kind::Number){o<<"i64.const "<<e.value;return;}
  if(e.kind==Expr::Kind::Name){o<<"local.get $"<<e.value;return;}
  if(e.kind==Expr::Kind::Unary){o<<"i64.const 0 ";wat_expr(*e.rhs,o);o<<" i64.sub";return;}
  if(e.kind==Expr::Kind::Call){for(auto&a:e.args){wat_expr(*a,o);o<<' ';}o<<"call $"<<e.value;return;}
  wat_expr(*e.lhs,o);o<<' ';wat_expr(*e.rhs,o);o<<' '; if(e.value=="+")o<<"i64.add";else if(e.value=="-")o<<"i64.sub";else if(e.value=="*")o<<"i64.mul";else if(e.value=="/")o<<"i64.div_s";else if(e.value=="==")o<<"i64.eq";else if(e.value=="!=")o<<"i64.ne";else if(e.value=="<")o<<"i64.lt_s";else if(e.value=="<=")o<<"i64.le_s";else if(e.value==">")o<<"i64.gt_s";else if(e.value==">=")o<<"i64.ge_s";
}
std::string emit_wat(const Program&p){std::ostringstream o;o<<"(module\n";for(auto&f:p.functions){o<<"  (func $"<<f.name<<"";for(auto&x:f.params)o<<" (param $"<<x<<" i64)";o<<" (result i64)\n    ";wat_expr(*f.body,o);o<<"\n  )\n";}o<<")\n";return o.str();}

static void x86_expr(const Expr&e,std::ostringstream&o,const Function&f){
  if(e.kind==Expr::Kind::Number){o<<"  mov $"<<e.value<<", %rax\n";return;}
  if(e.kind==Expr::Kind::Name){auto it=std::find(f.params.begin(),f.params.end(),e.value);if(it==f.params.end())throw Error("native backend unknown name: "+e.value,e.line,e.col);static const char* regs[]={"%rdi","%rsi","%rdx","%rcx","%r8","%r9"};auto idx=std::distance(f.params.begin(),it);if(idx>=6)throw Error("native backend supports up to 6 integer parameters",e.line,e.col);o<<"  mov "<<regs[idx]<<", %rax\n";return;}
  if(e.kind==Expr::Kind::Unary){x86_expr(*e.rhs,o,f);o<<"  neg %rax\n";return;}
  if(e.kind==Expr::Kind::Binary){x86_expr(*e.lhs,o,f);o<<"  push %rax\n";x86_expr(*e.rhs,o,f);o<<"  mov %rax, %rcx\n  pop %rax\n";if(e.value=="+")o<<"  add %rcx, %rax\n";else if(e.value=="-")o<<"  sub %rcx, %rax\n";else if(e.value=="*")o<<"  imul %rcx, %rax\n";else if(e.value=="/")o<<"  cqo\n  idiv %rcx\n";else {o<<"  cmp %rcx, %rax\n  ";if(e.value=="==")o<<"sete %al\n";else if(e.value=="!=")o<<"setne %al\n";else if(e.value=="<")o<<"setl %al\n";else if(e.value=="<=")o<<"setle %al\n";else if(e.value==">")o<<"setg %al\n";else if(e.value==">=")o<<"setge %al\n";o<<"  movzbq %al, %rax\n";}return;}
  throw Error("native backend does not yet lower strings/calls",e.line,e.col);
}
std::string emit_x86_64(const Program&p){std::ostringstream o;o<<".text\n";for(auto&f:p.functions){o<<".globl "<<f.name<<"\n"<<f.name<<":\n";x86_expr(*f.body,o,f);o<<"  ret\n";}return o.str();}
static void fmt_expr(const Expr&e,std::ostringstream&o){if(e.kind==Expr::Kind::Number||e.kind==Expr::Kind::String||e.kind==Expr::Kind::Name){o<<e.value;return;}if(e.kind==Expr::Kind::Call){o<<e.value<<"(";for(size_t i=0;i<e.args.size();++i){if(i)o<<", ";fmt_expr(*e.args[i],o);}o<<")";return;}if(e.kind==Expr::Kind::Unary){o<<e.value;fmt_expr(*e.rhs,o);return;}o<<"(";fmt_expr(*e.lhs,o);o<<" "<<e.value<<" ";fmt_expr(*e.rhs,o);o<<")";}
std::string format_program(const Program&p){std::ostringstream o;for(auto&f:p.functions){o<<"fn "<<f.name<<"(";for(size_t i=0;i<f.params.size();++i){if(i)o<<", ";o<<f.params[i];}o<<") -> ";fmt_expr(*f.body,o);o<<"\n";}return o.str();}

} // namespace aether
