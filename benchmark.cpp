#include "aether/aether.hpp"
#include <chrono>
#include <iostream>
int main(){const char*s="fn add(a,b) -> a+b\n";auto p=aether::parse(aether::lex(s));aether::VM vm(p);volatile long long sink=0;auto t0=std::chrono::steady_clock::now();for(int i=0;i<1000000;i++)sink += vm.call("add",{aether::Value::integer(i),aether::Value::integer(2)}).i;auto ms=std::chrono::duration<double,std::milli>(std::chrono::steady_clock::now()-t0).count();std::cout<<"vm_add_1m_ms="<<ms<<" sink="<<sink<<"\n";return sink==500001500000LL?0:1;}
