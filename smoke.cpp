#include "aether/aether.hpp"
#include <cassert>
#include <sstream>
int main(){const char* s="fn add(a, b) -> a + b\nfn square(x) -> x * x\nfn compare(a,b) -> a >= b\n"; auto p=aether::parse(aether::lex(s)); aether::VM vm(p); assert(vm.call("add",{aether::Value::integer(2),aether::Value::integer(3)}).i==5); assert(vm.call("square",{aether::Value::integer(7)}).i==49); assert(vm.call("compare",{aether::Value::integer(7),aether::Value::integer(3)}).b); auto w=aether::emit_wat(p); assert(w.find("i64.add")!=std::string::npos); auto a=aether::emit_x86_64(p); assert(a.find("add:")!=std::string::npos); return 0;}
