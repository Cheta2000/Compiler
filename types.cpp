#include "types.hpp"
#include "code.hpp"

#include <string>
#include <iostream>

OPERATOR operator-(OPERATOR &cond)
{
    switch (cond)
    {
    case OPERATOR::EQ:
        return OPERATOR::NEQ;
    case OPERATOR::NEQ:
        return OPERATOR::EQ;
    case OPERATOR::LE:
        return OPERATOR::GEQ;

    case OPERATOR::GE:
        return OPERATOR::LEQ;

    case OPERATOR::LEQ:
        return OPERATOR::GE;
    case OPERATOR::GEQ:
        return OPERATOR::LE;
    default:
        return cond;
    }
}

Type *ID::get_variable()
{
    if (Iterator *v = dynamic_cast<Iterator *>(this->var))
    {
        if (!v->get_init())
        {
            throw std::string("Variable " + v->get_id() + " not declared");
        }
    };
    return this->var;
}

ID_PID::ID_PID(std::string pidentifier)
{
    this->var = memory->find_in_memory(pidentifier);
    if (dynamic_cast<Array *>(this->var))
    {
        throw std::string("Invalid usage of array " + pidentifier);
    }
}

long long int ID_PID::get_memAddress()
{
    if (this->get_variable()->get_init())
    {
        return this->get_variable()->get_memAddress();
    }
    else
    {
        throw std::string("Variable " + this->get_variable()->get_id() + " not initialized");
    }
}

void ID_PID::init_ID()
{
    this->get_variable()->set_init();
}

ID_VALUE_ARRAY::ID_VALUE_ARRAY(std::string pidentifier, long long int num)
{
    this->var = (Array *)(memory->find_in_memory(pidentifier));
    this->index = num;
    if (Variable *v = dynamic_cast<Variable *>(this->var))
    {
        throw std::string("Invalid usage of variable " + pidentifier);
    }
}

long long int ID_VALUE_ARRAY::get_memAddress()
{
    if (auto *v = dynamic_cast<Array *>(this->get_variable()))
    {
        if (v->get_init(this->index) or this->get_variable()->get_init())
        {
            return v->get_memAddress(this->index);
        }
        else
        {
            throw std::string("Variable not initialized " + this->get_variable()->get_id() + "[" + std::to_string(this->index) + "]");
        }
    }
    else
    {
        throw std::string("Type error");
    }
}

void ID_VALUE_ARRAY::init_ID()
{
    if (Array *v = dynamic_cast<Array *>(this->get_variable()))
    {
        v->set_init(this->index);
    }
    else
    {
        throw std::string("Type error");
    }
}

ID_PID_ARRAY ::ID_PID_ARRAY(std::string pidentifier1, std::string pidentifier2)
{
    this->arrIndex = memory->find_in_memory(pidentifier2);
    if (Iterator *v = dynamic_cast<Iterator *>(this->arrIndex))
    {
        this->var = (Array *)(memory->find_in_memory(pidentifier1));
        if (Variable *v = dynamic_cast<Variable *>(this->var))
        {
            throw std::string("Invalid usage of variable " + this->get_variable()->get_id());
        }
    }
    else
    {
        this->var = (Array *)(memory->find_in_memory(pidentifier1));
        if (Variable *v = dynamic_cast<Variable *>(this->var))
        {
            throw std::string("Invalid usage of variable " + this->get_variable()->get_id());
        }
    }
}

long long int ID_PID_ARRAY::get_memAddress()
{
    if (Array *v = dynamic_cast<Array *>(this->get_variable()))
    {
        if (v->check_init() or this->get_variable()->get_init())
        {
            if (Iterator *v = dynamic_cast<Iterator *>(this->arrIndex))
            {
                if (!this->arrIndex->get_init())
                {
                    throw std::string("Variable " + this->arrIndex->get_id() + " not declared");
                }
            }
            if (this->arrIndex->get_init())
            {
                return v->get_memAddress();
            }
            else
            {
                throw std::string("Variable " + this->arrIndex->get_id() + " not initialized");
            }
        }
        else
        {
            throw std::string("Array " + this->get_variable()->get_id() + " not initialized");
        }
    }
    else
    {
        throw std::string("Type error");
    }
}

long long int ID_PID_ARRAY::get_index_memAddress()
{
    return this->arrIndex->get_memAddress();
}

void ID_PID_ARRAY::init_ID()
{
    this->get_variable()->set_init();
}

VALUE_NUMBER::VALUE_NUMBER(long long int num)
{
    this->value = num;
}

long long int VALUE_NUMBER::get_value()
{
    return this->value;
}

VALUE_ID::VALUE_ID(ID *id)
{
    this->identifier = id;
}

long long int VALUE_ID::get_value()
{

    return this->identifier->get_memAddress();
}

ID *VALUE_ID ::get_id()
{
    return this->identifier;
}

EXPRESSION_VALUE::EXPRESSION_VALUE(VALUE *value)
{
    this->value = value;
}

std::tuple<VALUE *, VALUE *, BINARY> EXPRESSION_VALUE ::get_expression()
{
    return std::make_tuple(this->value, nullptr, static_cast<BINARY>(NULL));
}

EXPRESSION_BINARY::EXPRESSION_BINARY(VALUE *value1, VALUE *value2, BINARY op)
{
    this->value1 = value1;
    this->value2 = value2;
    this->op = op;
}

std::tuple<VALUE *, VALUE *, BINARY> EXPRESSION_BINARY ::get_expression()
{
    return std::make_tuple(this->value1, this->value2, this->op);
}

CONDITION::CONDITION(VALUE *value1, VALUE *value2, OPERATOR cond)
{
    this->value1 = value1;
    this->value2 = value2;
    this->cond = cond;
}

void CONDITION::set_jump(long long int jump)
{
    this->jumpAddress = jump;
}

long long int CONDITION::get_jump()
{
    return this->jumpAddress;
}

void CONDITION::set_cond(long long int cond)
{
    this->condAddress = cond;
}

long long int CONDITION::get_cond()
{
    return this->condAddress;
}

void CONDITION::reverse_cond()
{
    this->cond = -this->cond;
}

std::tuple<VALUE *, VALUE *, OPERATOR> CONDITION::get_condition()
{
    return std::make_tuple(this->value1, this->value2, this->cond);
}

ASSIGN_COMMAND::ASSIGN_COMMAND(ID *id, EXPRESSION *expression)
{
    this->id = id;
    this->expression = expression;
}

void ASSIGN_COMMAND::load_command()
{
    code->assign(this->id, this->expression);
}

READ_COMMAND::READ_COMMAND(ID *id)
{
    this->id = id;
}

void READ_COMMAND::load_command()
{
    code->read(this->id);
}

WRITE_COMMAND::WRITE_COMMAND(VALUE *value)
{
    this->value = value;
}

void WRITE_COMMAND::load_command()
{
    code->write(this->value);
}

IF_THEN_COMMAND::IF_THEN_COMMAND(CONDITION *condition, std::vector<COMMAND *> *commands)
{
    this->condition = condition;
    this->commands = commands;
}

void IF_THEN_COMMAND::load_command()
{
    code->if_then(this->condition, this->commands);
}

IF_THEN_ELSE_COMMAND::IF_THEN_ELSE_COMMAND(CONDITION *condition, std::vector<COMMAND *> *commands, std::vector<COMMAND *> *elseCommands) : IF_THEN_COMMAND(condition, commands)
{
    this->elseCommands = elseCommands;
}

void IF_THEN_ELSE_COMMAND::load_command()
{
    code->if_then_else(this->condition, this->commands, this->elseCommands);
}

WHILE_COMMAND::WHILE_COMMAND(CONDITION *condition, std::vector<COMMAND *> *commands)
{
    this->condition = condition;
    this->commands = commands;
}

void WHILE_COMMAND::load_command()
{
    code->while_loop(this->condition, this->commands);
}

REPEAT_COMMAND::REPEAT_COMMAND(std::vector<COMMAND *> *commands, CONDITION *condition)
{
    this->condition = condition;
    this->condition->reverse_cond();
    this->commands = commands;
}

void REPEAT_COMMAND::load_command()
{
    code->repeat_loop(this->condition, this->commands);
}

FOR_UP_COMMAND::FOR_UP_COMMAND(std::string pidentifier, VALUE *value1, VALUE *value2, std::vector<COMMAND *> *commands)
{
    this->pidentifier = pidentifier;
    this->value1 = value1;
    this->value2 = value2;
    this->commands = commands;
}

void FOR_UP_COMMAND::load_command()
{
    code->for_up_loop(this->pidentifier, this->value1, this->value2, this->commands);
}

FOR_DOWN_COMMAND::FOR_DOWN_COMMAND(std::string pidentifier, VALUE *value1, VALUE *value2, std::vector<COMMAND *> *commands)
{
    this->pidentifier = pidentifier;
    this->value1 = value1;
    this->value2 = value2;
    this->commands = commands;
}

void FOR_DOWN_COMMAND::load_command()
{
    code->for_down_loop(this->pidentifier, this->value1, this->value2, this->commands);
}
