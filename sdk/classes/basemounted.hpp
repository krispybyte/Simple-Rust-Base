#pragma once
#include "../../common.hpp"

class BaseMounted
{
public:
    void setCanHoldItems(bool value)
    {
        memory.write<bool>(reinterpret_cast<uintptr_t>(this) + o::BaseMountable_canWieldItems, value);
    }
};