#include "aether/aether.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

static std::string read_all(const std::string& p){std::ifstream f(p);if(!f)throw std::runtime_error("cannot open "+p);std::ostringstream s;s<<f.rdbuf();return s.str();}
static void usage(){std::cerr<<"aetherc <check|run|fmt|wat|asm> file.ae [function args...]\n";}
int main(int argc,char**argv){try{if(argc<3){usage();return 2;}auto cmd=std::string(argv[1]);auto src=read_all(argv[2]);auto prog=aether::parse(aether::lex(src));if(cmd=="check"){std::cout<<"OK functions="<<prog.functions.size()<<"\n";return 0;}if(cmd=="fmt"){std::cout<<aether::format_program(prog);return 0;}if(cmd=="wat"){std::cout<<aether::emit_wat(prog);return 0;}if(cmd=="asm"){std::cout<<aether::emit_x86_64(prog);return 0;}if(cmd=="run"){if(argc<4){std::cerr<<"run requires function name\n";return 2;}std::vector<aether::Value> args;for(int i=4;i<argc;++i)args.push_back(aether::Value::integer(std::stoll(argv[i])));auto v=aether::VM(prog).call(argv[3],args);if(v.kind==aether::Value::Kind::Bool)std::cout<<(v.b?"true":"false")<<"\n";else if(v.kind==aether::Value::Kind::String)std::cout<<v.s<<"\n";else std::cout<<v.i<<"\n";return 0;}usage();return 2;}catch(const aether::Error&e){std::cerr<<"AETHER error:"<<e.line<<":"<<e.col<<": "<<e.what()<<"\n";return 1;}catch(const std::exception&e){std::cerr<<"AETHER error: "<<e.what()<<"\n";return 1;}}
