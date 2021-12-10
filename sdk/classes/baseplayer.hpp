#pragma once
#include "../../common.hpp"

struct bounding_box_t
{
    float x, y, w, h;
    Vector3 head_world{};
    Vector2 head_screen{};
    Vector3 foot_world{};
    Vector2 foot_screen{};
};

class BasePlayer
{
private:
public:
    uintptr_t getAddress()
    {
        return reinterpret_cast<uintptr_t>(this);
    }

    PlayerModel* playerModel()
    {
        return memory.read<PlayerModel*>(reinterpret_cast<uintptr_t>(this) + o::BasePlayer_playerModel);
    }

    PlayerInput* playerInput()
    {
        return memory.read<PlayerInput*>(reinterpret_cast<uintptr_t>(this) + o::BasePlayer_playerInput);
    }

    PlayerEyes* eyes()
    {
        return memory.read<PlayerEyes*>(reinterpret_cast<uintptr_t>(this) + o::BasePlayer_eyes);
    }
    
    ModelState* modelState()
    {
        return memory.read<ModelState*>(reinterpret_cast<uintptr_t>(this) + o::BasePlayer_modelstate);
    }

    PlayerWalkMovement* playerWalkMovement()
    {
        return memory.read<PlayerWalkMovement*>(reinterpret_cast<uintptr_t>(this) + o::BasePlayer_playerWalkMovement);
    }

    BaseMounted* mounted()
    {
        return memory.read<BaseMounted*>(reinterpret_cast<uintptr_t>(this) + o::BasePlayer_mounted);
    }

    void rebuildClothes()
    {
        memory.write<bool>(reinterpret_cast<uintptr_t>(this) + o::BasePlayer_needsClothesRebuild, true);
    }

    void setClientTickInterval(float interval)
    {
        memory.write<float>(reinterpret_cast<uintptr_t>(this) + o::BasePlayer_clientTickInterval, interval);
    }

    bool isDead()
    {
        return memory.read<int>(reinterpret_cast<uintptr_t>(this) + o::BaseCombatEntity_lifestate);
    }

    std::string getName()
    {
        std::wstring wname = memory.read_wstr(memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + o::BasePlayer_displayName) + 0x14);

        if (wname.length() > 32 || wname.length() < 2)
            return _("");

        return std::string(wname.begin(), wname.end());
    }

    float getLastSentTickTime()
    {
        return memory.read<float>(reinterpret_cast<uintptr_t>(this) + o::BasePlayer_lastSentTickTime);
    }

    int getDistance(Vector3 to_position)
    {
        return getBone(bone_list::head).distance(to_position);
    }

    float getHealth()
    {
        return memory.read<float>(reinterpret_cast<uintptr_t>(this) + o::BaseCombatEntity_health);
    }

    float getMaxHealth()
    {
        return memory.read<float>(reinterpret_cast<uintptr_t>(this) + o::BaseCombatEntity_maxHealth);
    }

    Item* getHeldItem()
    {
        int active_id = memory.read<int>(reinterpret_cast<uintptr_t>(this) + 0x5d0);

        uintptr_t inventory = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x690);

        uintptr_t contianer_belt = memory.read<uintptr_t>(inventory + 0x28);

        uintptr_t contents = memory.read<uintptr_t>(contianer_belt + 0x38);

        int size = memory.read<int>(contents + 0x18);

        contents = memory.read<uintptr_t>(contents + 0x10);

        for (int i = 0; i < size; i++)
        {
            Item* item = memory.read<Item*>(contents + (0x20 + (i * 0x8)));

            uintptr_t item_id = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(item) + 0x28);

            if (item_id == active_id)
                return item;
        }

        return nullptr;
    }

    bool isAiming()
    {
        return getHeldItem()->baseProjectile()->isAiming();
    }

    static enum Flags
    {
        Unused1 = 1,
        Unused2 = 2,
        IsAdmin = 4,
        ReceivingSnapshot = 8,
        Sleeping = 16,
        Spectating = 32,
        Wounded = 64,
        IsDeveloper = 128,
        Connected = 256,
        ThirdPersonViewmode = 1024,
        EyesViewmode = 2048,
        ChatMute = 4096,
        NoSprint = 8192,
        Aiming = 16384,
        DisplaySash = 32768,
        Relaxed = 65536,
        SafeZone = 131072,
        ServerFall = 262144,
        Incapacitated = 524288,
        Workbench1 = 1048576,
        Workbench2 = 2097152,
        Workbench3 = 4194304
    };

    /*  
    * change isLocalPlayer and isNpc to
    * playerModel()->isLocalPlayer();
    * etc
    */
    bool isLocalPlayer()
    {
        return playerModel()->isLocalPlayer();
    }

    bool isNPC()
    {
        return playerModel()->isNPC();
    }

    bool hasFlag(Flags flag) { return (memory.read<int>(reinterpret_cast<uintptr_t>(this) + o::BasePlayer_playerFlags)) & flag; }

    void setFlag(Flags flag)
    {
        int current_flags = memory.read<int>(reinterpret_cast<uintptr_t>(this) + o::BasePlayer_playerFlags);
        memory.write<int>(reinterpret_cast<uintptr_t>(this) + o::BasePlayer_playerFlags, current_flags |= flag);
    }

    void unsetFlag(Flags flag)
    {
        int player_flags = memory.read<int>(reinterpret_cast<uintptr_t>(this) + o::BasePlayer_playerFlags);

        if (hasFlag(flag))
            player_flags -= flag;

        memory.write<int>(reinterpret_cast<uintptr_t>(this) + o::BasePlayer_playerFlags, player_flags);
    }

    Vector3 getBone(bone_list _bone) { return bone.get_entity_bone(reinterpret_cast<uintptr_t>(this), _bone); }

    bounding_box_t getBoundingBox()
    {
        bounding_box_t box{};

        box.head_world = getBone(head).operator+(Vector3(0.f, 0.2f, 0.f));
        box.foot_world = getBone(l_foot).operator+(getBone(r_foot)).operator/(2);

        if (world_to_screen(box.head_world, box.head_screen) &&
            world_to_screen(box.foot_world, box.foot_screen))
        {
            box.h = box.head_screen.y - box.foot_screen.y;
            box.w = 2.f * (box.h / 4.f);
            box.x = box.foot_screen.x - Vector2(box.w / 2, 0).x;
            box.y = box.foot_screen.y - Vector2(box.w / 2, 0).y;
        }

        return box;
    }
};