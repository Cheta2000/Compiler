
#include <iostream>
#include <string>
#include <algorithm>

#include "memory.hpp"

void Memory::declare_variable(std::string id)
{

    if (exist(id))
    {
        throw std::string("Variable " + id + " already defined");
    }
    else
    {
        this->symbols[id] = new Variable(this->memPointer, id);
        this->memPointer++;
    }
}

void Memory::declare_array(std::string id, long long int start, long long int end)
{
    if (exist(id))
    {
        throw std::string("Array " + id + " already defined");
    }
    else
    {

        this->symbols[id] = new Array(this->memPointer, id, start, end);
        this->memPointer += end - start + 1;
    }
}

Iterator *Memory::create_iterator(std::string id)
{
    if (exist(id))
    {
        this->symbols[id]->set_memAddress(this->memPointer);
        this->memPointer += 2;
    }
    else
    {
        this->symbols[id] = new Iterator(this->memPointer, id);
        this->memPointer += 2;
    }
    this->symbols[id]->set_init();
    return static_cast<Iterator *>(this->symbols[id]);
}

void Memory::delete_iterator(std::string id)
{
    if (Iterator *v = dynamic_cast<Iterator *>(this->symbols[id]))
    {
        this->symbols[id]->set_uninit();
    }
}

Type *Memory::find_in_memory(std::string id)
{
    if (exist(id))
    {
        return this->symbols[id];
    }
    else
    {
        this->symbols[id] = new Iterator(this->memPointer, id);
        this->memPointer++;
        return this->symbols[id];
    }
}

bool Memory::exist(std::string id)
{
    if (this->symbols.count(id) != 0)
    {
        return true;
    }
    return false;
}

Type::Type(long long int memAddress, std::string id)
{
    this->memAddress = memAddress;
    this->id = id;
}

long long int Type ::get_memAddress()
{
    return this->memAddress;
}

void Type::set_memAddress(long long int address)
{
    this->memAddress = address;
}

void Type::set_init()
{
    this->initialized = true;
}

void Type::set_uninit()
{
    this->initialized = false;
}

bool Type::get_init()
{
    return this->initialized;
}

std::string Type::get_id()
{
    return this->id;
}

Array::Array(long long int memAddress, std::string id, long long int start, long long int end) : Type(memAddress, id)
{
    if (start <= end)
    {
        this->start = start;
        this->end = end;
    }
    else
    {
        throw std::string("Array " + id + " has greater start then end");
    }
}

long long int Array::get_memAddress(long long int index)
{
    if (index >= this->start && index <= this->end)
    {
        return this->memAddress + index - this->start;
    }
    else
    {
        throw std::string("Array " + this->get_id() + " index " + std::to_string(index) + " out of bounds");
    }
}

long long int Array::get_memAddress()
{
    return this->memAddress - this->start;
}

void Array::set_init(long long int index)
{
    this->initialized.push_back(index);
}

bool Array::get_init(long long int index)
{
    if (std::find(this->initialized.begin(), this->initialized.end(), index) != this->initialized.end())
    {
        return true;
    }
    return false;
}

bool Array::check_init()
{
    return this->initialized.size();
}
