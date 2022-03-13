#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Type
{
private:
    std::string id;

protected:
    bool initialized;
    long long int memAddress;

public:
    Type(long long int memAddress, std::string id);
    virtual ~Type() = default;
    long long int get_memAddress();
    void set_memAddress(long long int address);
    bool get_init();
    void set_init();
    void set_uninit();
    std::string get_id();
};

class Variable : public Type
{

protected:
    bool initialized = false;

public:
    using Type::Type;
};

class Iterator : public Variable
{
public:
    using Variable::Variable;
};

class Array : public Type
{
private:
    long long int start, end;
    std::vector<long long int> initialized;

public:
    Array(long long int memAddress, std::string id, long long int start, long long int end);
    long long int get_memAddress(long long int index);
    long long int get_memAddress();
    bool get_init(long long int index);
    bool check_init();
    void set_init(long long int index);
};

class Memory
{

public:
    void declare_variable(std::string id);
    void declare_array(std::string id, long long int start, long long int end);
    Iterator *create_iterator(std::string id);
    void delete_iterator(std::string id);
    Type *find_in_memory(std::string id);

private:
    long long int memPointer = 0;
    std::unordered_map<std::string, Type *> symbols;
    bool exist(std::string id);
};