#include "machine.hpp"
#include <string>

Register Registers::A = Register("a");
Register Registers::B = Register("b");
Register Registers::C = Register("c");
Register Registers::D = Register("d");
Register Registers::E = Register("e");
Register Registers::F = Register("f");
Register Registers::G = Register("g");
Register Registers::H = Register("h");

std::string Instructions::get()
{
    return "GET";
}
std::string Instructions::put()
{
    return "PUT";
}
std::string Instructions::load(Register reg)
{
    return "LOAD " + reg.id;
}
std::string Instructions::store(Register reg)
{
    return "STORE " + reg.id;
}
std::string Instructions::add(Register reg)
{
    return "ADD " + reg.id;
}
std::string Instructions::sub(Register reg)
{
    return "SUB " + reg.id;
}
std::string Instructions::shift(Register reg)
{
    return "SHIFT " + reg.id;
}
std::string Instructions::swap(Register reg)
{
    return "SWAP " + reg.id;
}
std::string Instructions::reset(Register reg)
{
    return "RESET " + reg.id;
}
std::string Instructions::inc(Register reg)
{
    return "INC " + reg.id;
}
std::string Instructions::dec(Register reg)
{
    return "DEC " + reg.id;
}
std::string Instructions::jump(long long int address)
{
    return "JUMP " + std::to_string(address);
}
std::string Instructions::jpos(long long int address)
{
    return "JPOS " + std::to_string(address);
}
std::string Instructions::jzero(long long int address)
{
    return "JZERO " + std::to_string(address);
}
std::string Instructions::jneg(long long int address)
{
    return "JNEG " + std::to_string(address);
}
std::string Instructions::halt()
{
    return "HALT";
}