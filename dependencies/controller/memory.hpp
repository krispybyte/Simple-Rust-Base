#pragma once
#include "controller.hpp"

/*
* replace with your functions
*/

#define STR_BUFFER_SIZE 64
#define WSTR_BUFFER_SIZE 1024

class memory_t
{
private:
public:
    uintptr_t module_base(const char* module_name)
    {
        return NULL;
    }

    void read(uintptr_t address, void* buffer, size_t size)
    {
        return;
    }

    template <typename t>
    t read(uintptr_t address)
    {
        t cum{};
        return cum;
    }

    std::string read_str(uintptr_t address, int size = STR_BUFFER_SIZE)
    {
        std::unique_ptr<char[]> buffer(new char[size]);
        read(address, buffer.get(), size);
        return std::string(buffer.get());
    }

    std::wstring read_wstr(uintptr_t address)
    {
        wchar_t buffer[WSTR_BUFFER_SIZE * sizeof(wchar_t)];
        read(address, &buffer, WSTR_BUFFER_SIZE * sizeof(wchar_t));
        return std::wstring(buffer);
    }


    template <typename t>
    t read_chain(uintptr_t address, std::vector<uintptr_t> chain)
    {
        uintptr_t cur_read = address;

        for (int i = 0; i < chain.size() - 1; ++i)
            cur_read = read<uintptr_t>(cur_read + chain[i]);

        return read<t>(cur_read + chain[chain.size() - 1]);
    }

    template<typename v>
    bool write(uintptr_t address, const v& value)
    {
        return true;
    }

} memory;