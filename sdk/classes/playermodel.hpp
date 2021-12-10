#pragma once
#include "../../common.hpp"

#define SKINTYPE_FEMALE 1

class PlayerModel
{
public:
    Vector3 getTargetVelocity() { return memory.read<Vector3>(reinterpret_cast<uintptr_t>(this) + o::PlayerModel_newVelocity); }
    bool isLocalPlayer() { return memory.read<bool>(reinterpret_cast<uintptr_t>(this) + o::PlayerModel_isLocalPlayer); }
    bool isNPC() { return memory.read<bool>(reinterpret_cast<uintptr_t>(this) + o::PlayerModel_IsNPC);  }
    bool isVisible() { return memory.read<bool>(reinterpret_cast<uintptr_t>(this) + o::PlayerModel_visible); }

    void applyChams()
    {
        return;
    }
};