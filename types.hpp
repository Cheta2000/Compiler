#pragma once

#include <string>
#include <tuple>
#include "memory.hpp"

class Code;
extern Code *code;
extern Memory *memory;

enum class BINARY
{
    PLUS,
    MINUS,
    TIMES,
    DIV,
    MOD
};

enum class OPERATOR
{
    EQ,
    NEQ,
    LE,
    GE,
    LEQ,
    GEQ
};

class ID
{
public:
    virtual long long int get_memAddress()
    {
        return 0;
    };
    virtual void init_ID(){};
    Type *get_variable();
    virtual ~ID() = default;

protected:
    Type *var;
};

class ID_PID : public ID
{
public:
    explicit ID_PID(std::string pidentifier);
    long long int get_memAddress() override;
    void init_ID() override;
};

class ID_PID_ARRAY : public ID
{
private:
    Type *arrIndex;

public:
    ID_PID_ARRAY(std::string pidentifier1, std::string pidentifier2);
    long long int get_memAddress() override;
    long long int get_index_memAddress();
    void init_ID() override;
};

class ID_VALUE_ARRAY : public ID
{
public:
    ID_VALUE_ARRAY(std::string pidentifier1, long long int num);
    long long int get_memAddress() override;
    void init_ID() override;

private:
    long long int index;
};

class VALUE
{
public:
    virtual long long int get_value()
    {
        return 0;
    };
};

class VALUE_NUMBER : public VALUE
{
private:
    long long int value;
    long long int get_value() override;

public:
    VALUE_NUMBER(long long int num);
};

class VALUE_ID : public VALUE
{
public:
    ID *get_id();

private:
    ID *identifier;
    long long int get_value() override;

public:
    VALUE_ID(ID *id);
};

class EXPRESSION
{
public:
    virtual std::tuple<VALUE *, VALUE *, BINARY> get_expression()
    {
        return std::make_tuple(nullptr, nullptr, static_cast<BINARY>(NULL));
    }
};

class EXPRESSION_VALUE : public EXPRESSION
{
public:
    std::tuple<VALUE *, VALUE *, BINARY> get_expression() override;
    EXPRESSION_VALUE(VALUE *value);

private:
    VALUE *value;
};

class EXPRESSION_BINARY : public EXPRESSION
{
private:
    VALUE *value1;
    VALUE *value2;
    BINARY op;

public:
    EXPRESSION_BINARY(VALUE *value1, VALUE *value2, BINARY op);
    std::tuple<VALUE *, VALUE *, BINARY> get_expression() override;
};

class CONDITION
{
private:
    VALUE *value1;
    VALUE *value2;
    OPERATOR cond;
    long long int jumpAddress;
    long long int condAddress;

public:
    CONDITION(VALUE *value1, VALUE *value2, OPERATOR cond);
    std::tuple<VALUE *, VALUE *, OPERATOR> get_condition();
    void set_jump(long long int jump);
    long long int get_jump();
    void set_cond(long long int cond);
    long long int get_cond();
    void reverse_cond();
};

class COMMAND
{
public:
    virtual void load_command(){};
};

class ASSIGN_COMMAND : public COMMAND
{
private:
    ID *id;
    EXPRESSION *expression;

public:
    ASSIGN_COMMAND(ID *id, EXPRESSION *expression);
    void load_command();
};

class READ_COMMAND : public COMMAND
{
private:
    ID *id;

public:
    READ_COMMAND(ID *id);
    void load_command();
};
class WRITE_COMMAND : public COMMAND
{

private:
    VALUE *value;

public:
    WRITE_COMMAND(VALUE *value);
    void load_command();
};

class IF_THEN_COMMAND : public COMMAND
{
protected:
    CONDITION *condition;
    std::vector<COMMAND *> *commands;

public:
    IF_THEN_COMMAND(CONDITION *condition, std::vector<COMMAND *> *commands);
    void load_command();
};
class IF_THEN_ELSE_COMMAND : public IF_THEN_COMMAND
{
private:
    std::vector<COMMAND *> *elseCommands;

public:
    IF_THEN_ELSE_COMMAND(CONDITION *condition, std::vector<COMMAND *> *commands, std::vector<COMMAND *> *elseCommands);
    void load_command();
};

class WHILE_COMMAND : public COMMAND
{
private:
    CONDITION *condition;
    std::vector<COMMAND *> *commands;

public:
    WHILE_COMMAND(CONDITION *condition, std::vector<COMMAND *> *commands);
    void load_command();
};

class REPEAT_COMMAND : public COMMAND
{
private:
    CONDITION *condition;
    std::vector<COMMAND *> *commands;

public:
    REPEAT_COMMAND(std::vector<COMMAND *> *commands, CONDITION *condition);
    void load_command();
};

class FOR_UP_COMMAND : public COMMAND, public ID
{
private:
    std::string pidentifier;
    VALUE *value1;
    VALUE *value2;
    std::vector<COMMAND *> *commands;

public:
    FOR_UP_COMMAND(std::string pidentifier, VALUE *value1, VALUE *value2, std::vector<COMMAND *> *commands);
    void load_command();
};

class FOR_DOWN_COMMAND : public COMMAND, public ID
{
private:
    std::string pidentifier;
    VALUE *value1;
    VALUE *value2;
    std::vector<COMMAND *> *commands;

public:
    FOR_DOWN_COMMAND(std::string pidentifier, VALUE *value1, VALUE *value2, std::vector<COMMAND *> *commands);
    void load_command();
};