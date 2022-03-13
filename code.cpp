#include "code.hpp"
#include "types.hpp"

#include <string>
#include <iostream>
#include <fstream>

//rejestry
// a glowny
// b adresy pamieci przy read write
// c przesuwanie lewo
// d przesuwanie prawo
// e miejsce w pamieci
// f dynamiczne miejsce w pamieci
// g wolny
// h generowanie stalych

//opt-for,przechowywanie zmiennych(rejestry).mnozenie,dzielenie,mod,znane znaki w operaacjach, pamiec

void Code::start_code()
{
    Register shiftLeft = Registers::C;
    Register shiftRight = Registers::D;
    this->instructions.push_back(Instructions::reset(shiftLeft));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(shiftLeft));
    this->codePointer++;
    this->instructions.push_back(Instructions::dec(shiftRight));
    this->codePointer++;
}

void Code::run_program(std::vector<COMMAND *> *commands)
{
    code->start_code();
    for (const auto &command : *commands)
    {
        command->load_command();
    }
    code->end_code();
}

void Code::end_code()
{
    instructions.push_back(Instructions::halt());
    this->codePointer++;
}

void Code::read(ID *id)
{
    Register regB = Registers::B;
    this->instructions.push_back(Instructions::get());
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->load_id(id);
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::store(regB));
    this->codePointer++;
}
void Code::write(VALUE *value)
{
    this->load_value(value);
    this->instructions.push_back(Instructions::put());
    this->codePointer++;
}

void Code::assign(ID *id, EXPRESSION *expression)
{
    Register regE = Registers::E;
    Register regG = Registers::G;
    this->load_expression(expression);
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    this->load_id(id);
    this->instructions.push_back(Instructions::swap(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::store(regE));
    this->codePointer++;
}

void Code::plus(VALUE *value1, VALUE *value2)
{
    Register regB = Registers::B;
    this->load_value(value1);
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->load_value(value2);
    this->instructions.push_back(Instructions::add(regB));
    this->codePointer++;
}
void Code::minus(VALUE *value1, VALUE *value2)
{
    Register regB = Registers::B;
    this->load_value(value2);
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->load_value(value1);
    this->instructions.push_back(Instructions::sub(regB));
    this->codePointer++;
}
void Code::times(VALUE *value1, VALUE *value2)
{
    Register mainReg = Registers::A;
    Register regB = Registers::B;
    Register regG = Registers::G;
    Register shiftLeft = Registers::C;
    Register shiftRight = Registers::D;
    Register regH = Registers::H;
    Register regF = Registers::F;
    this->load_value(value1);
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->load_value(value2);
    //MNIEJSZY DRUGI OPT
    // wartosci w a i b
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regH));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regF));
    this->codePointer++;
    // check a
    this->instructions.push_back(Instructions::jzero(27));
    this->codePointer++;
    this->instructions.push_back(Instructions::jpos(4));
    this->codePointer++;
    this->instructions.push_back(Instructions::dec(regH));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::sub(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    // check b
    this->instructions.push_back(Instructions::jzero(20));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    // parzystposc B
    this->instructions.push_back(Instructions::add(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::shift(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::shift(shiftLeft));
    this->codePointer++;
    this->instructions.push_back(Instructions::sub(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::jzero(4));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::add(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(2));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::shift(shiftLeft));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::shift(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(-20));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regH));
    this->codePointer++;
    this->instructions.push_back(Instructions::jzero(4));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(mainReg));
    this->codePointer++;
    this->instructions.push_back(Instructions::sub(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(2));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
}
void Code::div(VALUE *value1, VALUE *value2)
{
    Register mainReg = Registers::A;
    Register regB = Registers::B;
    Register shiftLeft = Registers::C;
    Register shiftRight = Registers::D;
    Register regE = Registers::E;
    Register regG = Registers::G;
    Register regF = Registers::F;
    Register regH = Registers::H;
    this->load_value(value1);
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->load_value(value2);
    this->instructions.push_back(Instructions::reset(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regH));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::jzero(66));
    this->codePointer++;
    this->instructions.push_back(Instructions::jpos(6));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::sub(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::jzero(58));
    this->codePointer++;
    this->instructions.push_back(Instructions::jpos(5));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::sub(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regF));
    this->codePointer++;
    // h=dlugosc bitowa a
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::add(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::jzero(4));
    this->codePointer++;
    this->instructions.push_back(Instructions::shift(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(regH));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(-3));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    // g dlugosc a wartosc
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    // g=dlugosc bitowa b
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::add(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::jzero(4));
    this->codePointer++;
    this->instructions.push_back(Instructions::shift(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(-3));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regH));
    this->codePointer++;
    // roznica dlugosci
    this->instructions.push_back(Instructions::sub(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::jneg(35));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::add(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(regF));
    this->codePointer++;
    // a roznica h g
    // wyrownanie do lewej
    this->instructions.push_back(Instructions::jzero(6));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::shift(shiftLeft));
    this->codePointer++;
    this->instructions.push_back(Instructions::dec(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(-5));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regH));
    this->codePointer++;
    // a i wyrownane b
    this->instructions.push_back(Instructions::reset(regH));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    // petla
    this->instructions.push_back(Instructions::jzero(19));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::add(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::sub(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regH));
    this->codePointer++;
    this->instructions.push_back(Instructions::shift(shiftLeft));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regH));
    this->codePointer++;
    this->instructions.push_back(Instructions::jneg(5));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(regH));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::sub(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::shift(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::dec(mainReg));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(-18));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(6));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regH));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::add(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regH));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regH));
    this->codePointer++;

    // spr
    this->instructions.push_back(Instructions::swap(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::jzero(16));
    this->codePointer++;
    this->instructions.push_back(Instructions::dec(mainReg));
    this->codePointer++;
    this->instructions.push_back(Instructions::jzero(4));
    this->codePointer++;
    this->instructions.push_back(Instructions::dec(mainReg));
    this->codePointer++;
    this->instructions.push_back(Instructions::jzero(2));
    this->codePointer++;
    // dwa minusy
    this->instructions.push_back(Instructions::jump(11));
    this->codePointer++;
    // jeden minus
    this->instructions.push_back(Instructions::reset(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::sub(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::jzero(4));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::sub(shiftLeft));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regE));
    this->codePointer++;
}
void Code::mod(VALUE *value1, VALUE *value2)
{
    Register mainReg = Registers::A;
    Register regB = Registers::B;
    Register shiftLeft = Registers::C;
    Register shiftRight = Registers::D;
    Register regE = Registers::E;
    Register regG = Registers::G;
    Register regF = Registers::F;
    Register regH = Registers::H;
    this->load_value(value1);
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->load_value(value2);
    this->instructions.push_back(Instructions::reset(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regH));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(shiftLeft));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(shiftLeft));
    this->codePointer++;
    this->instructions.push_back(Instructions::add(shiftLeft));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(shiftLeft));
    this->codePointer++;
    this->instructions.push_back(Instructions::jzero(74));
    this->codePointer++;
    this->instructions.push_back(Instructions::jpos(6));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::sub(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::jzero(66));
    this->codePointer++;
    this->instructions.push_back(Instructions::jpos(5));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::sub(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regF));
    this->codePointer++;
    // h=dlugosc bitowa a
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::add(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::jzero(4));
    this->codePointer++;
    this->instructions.push_back(Instructions::shift(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(regH));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(-3));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    // g dlugosc a wartosc
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    // g=dlugosc bitowa b
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::add(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::jzero(4));
    this->codePointer++;
    this->instructions.push_back(Instructions::shift(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(-3));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regH));
    this->codePointer++;
    // roznica dlugosci
    this->instructions.push_back(Instructions::sub(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::jneg(44));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::add(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(regF));
    this->codePointer++;
    // a roznica h g
    // wyrownanie do lewej
    this->instructions.push_back(Instructions::jzero(10));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::shift(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::dec(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::dec(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::dec(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(-9));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regH));
    this->codePointer++;
    // a i wyrownane b
    this->instructions.push_back(Instructions::reset(regH));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    // petla
    this->instructions.push_back(Instructions::jzero(23));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::add(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::sub(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regH));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::shift(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::dec(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::dec(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regH));
    this->codePointer++;
    this->instructions.push_back(Instructions::jneg(5));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(regH));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::sub(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::shift(shiftRight));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::dec(mainReg));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(-22));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(2));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regH));
    this->codePointer++;
    // spr
    this->instructions.push_back(Instructions::swap(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::jzero(21));
    this->codePointer++;
    this->instructions.push_back(Instructions::dec(mainReg));
    this->codePointer++;
    this->instructions.push_back(Instructions::jzero(13));
    this->codePointer++;
    this->instructions.push_back(Instructions::dec(mainReg));
    this->codePointer++;
    this->instructions.push_back(Instructions::jzero(7));
    this->codePointer++;
    // dwa minusy
    this->instructions.push_back(Instructions::reset(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::sub(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(11));
    this->codePointer++;
    // minus w B
    this->instructions.push_back(Instructions::swap(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::add(shiftLeft));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(7));
    this->codePointer++;
    // minus w A
    this->instructions.push_back(Instructions::reset(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::sub(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::add(shiftLeft));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regE));
    this->codePointer++;
    this->instructions.push_back(Instructions::reset(shiftLeft));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(shiftLeft));
    this->codePointer++;
}

void Code::print_to_file(std::string filename)
{
    std::ofstream myfile;
    myfile.open(filename);
    for (auto &line : this->instructions)
    {
        myfile << line << std::endl;
    }
    myfile.close();
}

void Code::create_const(long long int value)
{
    Register mainReg = Registers::A;
    this->instructions.push_back(Instructions::reset(mainReg));
    this->codePointer++;
    if (value != 0)
    {
        Register shiftReg = Registers::H;
        this->instructions.push_back(Instructions::reset(shiftReg));
        this->codePointer++;
        this->instructions.push_back(Instructions::inc(shiftReg));
        this->codePointer++;
        int shiftSize = 1;
        int zeros = 1;
        std::string bin = this->dec2bin(abs(value));
        if (value > 0)
        {
            for (std::string::size_type i = 0; i < bin.length() - 1; i++)
            {
                if (bin.at(i) == '1')
                {

                    this->instructions.push_back(Instructions::inc(mainReg));
                    this->codePointer++;
                    zeros = 1;
                }
                if (i + 1 < bin.length() - 1)
                {
                    if (bin.at(i + 1) == '0')
                    {
                        if (shiftSize <= zeros)
                        {
                            shiftSize++;
                            this->instructions.push_back(Instructions::inc(shiftReg));
                            this->codePointer++;
                        }
                        zeros++;
                    }
                    else
                    {
                        while (shiftSize != zeros)
                        {
                            shiftSize--;
                            this->instructions.push_back(Instructions::dec(shiftReg));
                            this->codePointer++;
                        }
                        this->instructions.push_back(Instructions::shift(shiftReg));
                        this->codePointer++;
                    }
                }
            }
            while (shiftSize != zeros)
            {
                shiftSize--;
                this->instructions.push_back(Instructions::dec(shiftReg));
                this->codePointer++;
            }
            this->instructions.push_back(Instructions::shift(shiftReg));
            this->codePointer++;
            if (bin[bin.length() - 1] == '1')
            {
                this->instructions.push_back(Instructions::inc(mainReg));
                this->codePointer++;
            }
        }
        else
        {
            for (std::string::size_type i = 0; i < bin.length() - 1; i++)
            {
                if (bin.at(i) == '1')
                {

                    this->instructions.push_back(Instructions::dec(mainReg));
                    this->codePointer++;
                    zeros = 1;
                }
                if (i + 1 < bin.length() - 1)
                {
                    if (bin.at(i + 1) == '0')
                    {
                        if (shiftSize <= zeros)
                        {
                            shiftSize++;
                            this->instructions.push_back(Instructions::inc(shiftReg));
                            this->codePointer++;
                        }
                        zeros++;
                    }
                    else
                    {
                        while (shiftSize != zeros)
                        {
                            shiftSize--;
                            this->instructions.push_back(Instructions::dec(shiftReg));
                            this->codePointer++;
                        }
                        this->instructions.push_back(Instructions::shift(shiftReg));
                        this->codePointer++;
                    }
                }
            }
            while (shiftSize != zeros)
            {
                shiftSize--;
                this->instructions.push_back(Instructions::dec(shiftReg));
                this->codePointer++;
            }
            this->instructions.push_back(Instructions::shift(shiftReg));
            this->codePointer++;
            if (bin[bin.length() - 1] == '1')
            {
                this->instructions.push_back(Instructions::dec(mainReg));
                this->codePointer++;
            }
        }
    }
}

void Code::print_code()
{
    for (auto &line : this->instructions)
    {
        std::cout << line << std::endl;
    }
}

std::string Code::dec2bin(long long int value)
{
    std::string bin = "";
    while (value > 0)
    {
        if (value % 2 == 1)
        {
            bin = "1" + bin;
        }
        else
        {
            bin = "0" + bin;
        }
        value /= 2;
    }
    return bin;
}

void Code::generate_dynamic_array_address(ID_PID_ARRAY *id)
{
    Register regF = Registers::F;
    Register mainReg = Registers::A;
    long long int indexInMem = id->get_index_memAddress();
    this->instructions.push_back(Instructions::swap(regF));
    this->codePointer++;
    this->create_const(indexInMem);
    this->instructions.push_back(Instructions::load(mainReg));
    this->codePointer++;
    this->instructions.push_back(Instructions::add(regF));
    this->codePointer++;
}

void Code::if_then(CONDITION *condition, std::vector<COMMAND *> *commands)
{
    this->load_condition(condition);
    for (const auto &command : *commands)
    {
        command->load_command();
    }
    this->change_jump_address(this->codePointer, condition->get_jump());
}
void Code::if_then_else(CONDITION *condition, std::vector<COMMAND *> *commands, std::vector<COMMAND *> *elseCommands)
{
    this->load_condition(condition);
    for (const auto &command : *commands)
    {
        command->load_command();
    }
    long long int elseStart = this->codePointer;
    this->instructions.push_back(Instructions::jump(0));
    this->codePointer++;
    this->change_jump_address(this->codePointer, condition->get_jump());
    for (const auto &command : *elseCommands)
    {
        command->load_command();
    }
    this->change_jump_address(this->codePointer, elseStart);
}

void Code::load_expression(EXPRESSION *expression)
{
    auto expr = expression->get_expression();
    VALUE *value1 = std::get<0>(expr);
    VALUE *value2 = std::get<1>(expr);
    BINARY binary = std::get<2>(expr);
    Register mainReg = Registers::A;
    Register regB = Registers::B;
    if (EXPRESSION_VALUE *v = dynamic_cast<EXPRESSION_VALUE *>(expression))
    {
        this->load_value(value1);
    }
    else
    {
        switch (binary)
        {
        case BINARY::PLUS:
            this->plus(value1, value2);
            break;
        case BINARY::MINUS:
            this->minus(value1, value2);
            break;
        case BINARY::TIMES:
            this->times(value1, value2);
            break;
        case BINARY::DIV:
            this->div(value1, value2);
            break;
        case BINARY::MOD:
            this->mod(value1, value2);
            break;
        default:
            break;
        }
    }
}

void Code::load_value(VALUE *value)
{
    Register mainReg = Registers::A;
    long long int val = value->get_value();
    this->create_const(val);
    if (VALUE_ID *v1 = dynamic_cast<VALUE_ID *>(value))
    {
        if (ID_PID_ARRAY *v2 = dynamic_cast<ID_PID_ARRAY *>(v1->get_id()))
        {
            generate_dynamic_array_address(v2);
        }
        this->instructions.push_back(Instructions::load(mainReg));
        this->codePointer++;
    }
}

void Code::load_condition(CONDITION *condition)
{
    auto cond = condition->get_condition();
    condition->set_cond(this->codePointer);
    VALUE *value1 = std::get<0>(cond);
    VALUE *value2 = std::get<1>(cond);
    OPERATOR op = std::get<2>(cond);
    EXPRESSION_BINARY *condExpression = new EXPRESSION_BINARY(value1, value2, BINARY::MINUS);
    this->load_expression(condExpression);
    condition->set_jump(this->codePointer);
    switch (op)
    {
    case OPERATOR::EQ:
        condition->set_jump(this->codePointer + 1);
        this->eq();
        break;
    case OPERATOR::NEQ:
        this->neq();
        break;
    case OPERATOR::LE:
        condition->set_jump(this->codePointer + 1);
        this->le();
        break;
    case OPERATOR::GE:
        condition->set_jump(this->codePointer + 1);
        this->ge();
        break;
    case OPERATOR::LEQ:
        this->leq();
        break;
    case OPERATOR::GEQ:
        this->geq();
        break;
    default:
        break;
    }
}

void Code::load_id(ID *id)
{
    if (Iterator *v = dynamic_cast<Iterator *>(id->get_variable()))
    {
        throw std::string("Cannot change iterator " + v->get_id());
    }
    Register mainReg = Registers::A;
    id->init_ID();
    long long int varInMem = id->get_memAddress();
    this->create_const(varInMem);
    if (ID_PID_ARRAY *v = dynamic_cast<ID_PID_ARRAY *>(id))
    {
        generate_dynamic_array_address(v);
    }
}

void Code::eq()
{
    this->instructions.push_back(Instructions::jzero(2));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(0));
    this->codePointer++;
}
void Code::neq()
{
    this->instructions.push_back(Instructions::jzero(0));
    this->codePointer++;
}
void Code::le()
{
    this->instructions.push_back(Instructions::jneg(2));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(0));
    this->codePointer++;
}
void Code::ge()
{
    this->instructions.push_back(Instructions::jpos(2));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(0));
    this->codePointer++;
}
void Code::leq()
{
    this->instructions.push_back(Instructions::jpos(0));
    this->codePointer++;
}
void Code::geq()
{
    this->instructions.push_back(Instructions::jneg(0));
    this->codePointer++;
}

void Code::change_jump_address(long long int codePointer, long long int jumpPointer)
{
    std::string &jump = this->instructions.at(jumpPointer);
    std::size_t pos = jump.find("0");
    if (pos != std::string::npos)
    {
        jump.replace(pos, 100, std::to_string(codePointer - jumpPointer));
    }
}

void Code::while_loop(CONDITION *condition, std::vector<COMMAND *> *commands)
{
    this->load_condition(condition);
    for (const auto &command : *commands)
    {
        command->load_command();
    }
    this->instructions.push_back(Instructions::jump(condition->get_cond() - this->codePointer));
    this->codePointer++;
    this->change_jump_address(this->codePointer, condition->get_jump());
}

void Code::repeat_loop(CONDITION *condition, std::vector<COMMAND *> *commands)
{
    long long int loop = this->codePointer;
    for (const auto &command : *commands)
    {
        command->load_command();
    }
    this->load_condition(condition);
    this->instructions.push_back(Instructions::jump(loop - this->codePointer));
    this->codePointer++;
    this->change_jump_address(this->codePointer, condition->get_jump());
}

// raczej do optymalizacji
void Code::for_up_loop(std::string pidentifier, VALUE *value1, VALUE *value2, std::vector<COMMAND *> *commands)
{
    Register mainReg = Registers::A;
    Register regB = Registers::B;
    Register regG = Registers::G;
    Iterator *iterator = memory->create_iterator(pidentifier);
    code->load_value(value2);
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    code->create_const(iterator->get_memAddress() + 1);
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    code->instructions.push_back(Instructions::store(regB));
    code->codePointer++;
    code->load_value(value1);
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    code->create_const(iterator->get_memAddress());
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    code->instructions.push_back(Instructions::store(regB));
    code->codePointer++;
    long long int loop = this->codePointer;
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    code->create_const(iterator->get_memAddress() + 1);
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::load(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::sub(regG));
    this->codePointer++;
    long long int loop2 = this->codePointer;
    this->instructions.push_back(Instructions::jpos(0));
    this->codePointer++;
    for (const auto &command : *commands)
    {
        command->load_command();
    }
    code->create_const(iterator->get_memAddress());
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::load(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::inc(mainReg));
    this->codePointer++;
    this->instructions.push_back(Instructions::store(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(loop - this->codePointer));
    this->codePointer++;
    this->change_jump_address(this->codePointer, loop2);
    memory->delete_iterator(pidentifier);
}

void Code::for_down_loop(std::string pidentifier, VALUE *value1, VALUE *value2, std::vector<COMMAND *> *commands)
{
    Register mainReg = Registers::A;
    Register regB = Registers::B;
    Register regG = Registers::G;
    Iterator *iterator = memory->create_iterator(pidentifier);
    code->load_value(value2);
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    code->create_const(iterator->get_memAddress() + 1);
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    code->instructions.push_back(Instructions::store(regB));
    code->codePointer++;
    code->load_value(value1);
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    code->create_const(iterator->get_memAddress());
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    code->instructions.push_back(Instructions::store(regB));
    code->codePointer++;
    long long int loop = this->codePointer;
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    code->create_const(iterator->get_memAddress() + 1);
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::load(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::swap(regG));
    this->codePointer++;
    this->instructions.push_back(Instructions::sub(regG));
    this->codePointer++;
    long long int loop2 = this->codePointer;
    this->instructions.push_back(Instructions::jneg(0));
    this->codePointer++;
    for (const auto &command : *commands)
    {
        command->load_command();
    }
    code->create_const(iterator->get_memAddress());
    this->instructions.push_back(Instructions::swap(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::load(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::dec(mainReg));
    this->codePointer++;
    this->instructions.push_back(Instructions::store(regB));
    this->codePointer++;
    this->instructions.push_back(Instructions::jump(loop - this->codePointer));
    this->codePointer++;
    this->change_jump_address(this->codePointer, loop2);
    memory->delete_iterator(pidentifier);
}