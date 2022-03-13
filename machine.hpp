#include <string>

class Register
{
public:
    std::string id;
    Register(std ::string reg) : id(reg){};
};

class Registers
{
public:
    static Register A;
    static Register B;
    static Register C;
    static Register D;
    static Register E;
    static Register F;
    static Register G;
    static Register H;
};

class Instructions
{

public:
    static std::string get();
    static std::string put();
    static std::string load(Register reg);
    static std::string store(Register reg);
    static std::string add(Register reg);
    static std::string sub(Register reg);
    static std::string shift(Register reg);
    static std::string swap(Register reg);
    static std::string reset(Register reg);
    static std::string inc(Register reg);
    static std::string dec(Register reg);
    static std::string jump(long long int address);
    static std::string jpos(long long int address);
    static std::string jzero(long long int address);
    static std::string jneg(long long int address);
    static std::string halt();
};