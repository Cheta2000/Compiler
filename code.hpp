#pragma once

#include <string>
#include <vector>

#include "types.hpp"
#include "machine.hpp"

class Code
{
public:
    void start_code();
    void end_code();
    void read(ID *id);
    void write(VALUE *value);
    void assign(ID *id, EXPRESSION *expression);
    void plus(VALUE *value1, VALUE *value2);
    void minus(VALUE *value1, VALUE *value2);
    void times(VALUE *value1, VALUE *value2);
    void div(VALUE *value1, VALUE *value2);
    void mod(VALUE *value1, VALUE *value2);
    void if_then(CONDITION *condition, std::vector<COMMAND *> *commands);
    void if_then_else(CONDITION *condition, std::vector<COMMAND *> *commands, std::vector<COMMAND *> *elseCommands);
    void eq();
    void neq();
    void le();
    void ge();
    void leq();
    void geq();
    void print_to_file(std::string filename);
    void print_code();
    void run_program(std::vector<COMMAND *> *commands);
    void load_expression(EXPRESSION *expression);
    void load_value(VALUE *value);
    void load_condition(CONDITION *condition);
    void load_id(ID *id);
    void change_jump_address(long long int codePointer, long long int jumpPointer);
    void while_loop(CONDITION *condition, std::vector<COMMAND *> *commands);
    void repeat_loop(CONDITION *condition, std::vector<COMMAND *> *commands);
    void for_up_loop(std::string pidentifier, VALUE *value1, VALUE *value2, std::vector<COMMAND *> *commands);
    void for_down_loop(std::string pidentifier, VALUE *value1, VALUE *value2, std::vector<COMMAND *> *commands);

private:
    std::vector<std::string> instructions;
    long long int codePointer = 0;
    void create_const(long long int value);
    void generate_dynamic_array_address(ID_PID_ARRAY *id);
    std::string dec2bin(long long int value);
};