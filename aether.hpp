#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <optional>
#include <stdexcept>

namespace aether {

enum class TokenKind { End, Identifier, Number, String, Let, Mut, Const, Fn, Return, If, Else,
  LParen, RParen, LBrace, RBrace, Comma, Colon, Arrow, Plus, Minus, Star, Slash,
  Eq, EqEq, NotEq, Lt, LtEq, Gt, GtEq, Newline };

struct Token { TokenKind kind; std::string text; std::size_t line=1, col=1; };

class Error : public std::runtime_error {
public:
  std::size_t line, col;
  Error(std::string msg, std::size_t l, std::size_t c) : std::runtime_error(std::move(msg)), line(l), col(c) {}
};

std::vector<Token> lex(std::string_view source);

struct Expr {
  enum class Kind { Number, String, Name, Binary, Call, Unary } kind;
  std::string value;
  std::vector<std::unique_ptr<Expr>> args;
  std::unique_ptr<Expr> lhs, rhs;
  std::size_t line=1, col=1;
};

struct Function {
  std::string name;
  std::vector<std::string> params;
  std::unique_ptr<Expr> body;
  std::size_t line=1, col=1;
};

struct Program { std::vector<Function> functions; };

Program parse(const std::vector<Token>& tokens);

struct Value {
  enum class Kind { Int, Float, String, Bool, Error } kind=Kind::Int;
  std::int64_t i=0;
  double f=0;
  std::string s;
  bool b=false;
  static Value integer(std::int64_t v); static Value boolean(bool v); static Value string(std::string v);
};

class VM {
public:
  explicit VM(const Program& p): program_(p) {}
  Value call(std::string_view name, const std::vector<Value>& args) const;
private:
  const Program& program_;
  const Function* find(std::string_view name) const;
  Value eval(const Expr& e, const std::unordered_map<std::string,Value>& env) const;
};

std::string emit_wat(const Program& p);
std::string emit_x86_64(const Program& p);
std::string format_program(const Program& p);

} // namespace aether
