#pragma once

/* libraries */
#include <Windows.h>
#include <cstdint>
#include <vector>
#include <iomanip>
#include <cmath>
#include <limits>
#include <algorithm>
#include <chrono>
#include <thread>
#include <unordered_map>

#include <d3d9.h>
#include <d3dx9tex.h>
#include <d3dx9.h>

/* encryption */
#include "dependencies/encryption/xor.hpp"

/* bypass */
#include "dependencies/controller/controller.hpp"

/* utils */
#include "dependencies/utils/utils.hpp"
#include "dependencies/utils/math.hpp"

/* global */
#include "globals.hpp"

/* imgui, fonts, images */
#include "dependencies/rendering/imgui/imgui.h"

/* sdk */
#include "sdk/offsets.hpp"
#include "sdk/classes/camera.hpp"
#include "sdk/classes/prefab.hpp"
#include "sdk/classes/basemounted.hpp"
#include "sdk/classes/itemdefinition.hpp"
#include "sdk/classes/projectile.hpp"
#include "sdk/classes/baseprojectile.hpp"
#include "sdk/classes/item.hpp"
#include "sdk/classes/bone.hpp"
#include "sdk/classes/playereyes.hpp"
#include "sdk/classes/modelstate.hpp"
#include "sdk/classes/playerinput.hpp"
#include "sdk/classes/playermodel.hpp"
#include "sdk/classes/playerwalkmovement.hpp"
#include "sdk/classes/baseplayer.hpp"
#include "sdk/game/players.hpp"
#include "sdk/game/entity_list.hpp"
#include "sdk/game/features.hpp"
#include "sdk/game/aimbot.hpp"