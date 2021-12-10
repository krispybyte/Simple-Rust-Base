#pragma once

#define rust_offset constexpr uintptr_t

namespace o
{
	// UnityPlayer (ida)
	rust_offset GameObjectManager = 0x17C1F18;

	// Script.json
	rust_offset BaseNetworkable_c = 0x3101700;
	rust_offset Graphics_c = 0x30FF330;

	// Graphics
	rust_offset grassshadows = 0x10;
	rust_offset contactshadows = 0x11;
	rust_offset Graphics_drawdistance = 0x14;
	rust_offset Graphics_fov = 0x18;
	rust_offset Graphics_hud = 0x1C;
	rust_offset Graphics_chat = 0x1D;

	// Base Player
	rust_offset BasePlayer_modelstate = 0x5F8;
	rust_offset BasePlayer_playerFlags = 0x680;
	rust_offset BasePlayer_playerModel = 0x4C0;
	rust_offset BasePlayer_playerInput = 0x4e0;
	rust_offset BasePlayer_playerWalkMovement = 0x4E8;
	rust_offset BasePlayer_clientTickInterval = 0x650;
	rust_offset BasePlayer_displayName = 0x6E0;
	rust_offset BasePlayer_eyes = 0x688;
	rust_offset BasePlayer_inventory = 0x690;
	rust_offset BasePlayer_needsClothesRebuild = 0x520;
	rust_offset BasePlayer_lastSentTickTime = 0x654;
	rust_offset BasePlayer_mounted = 0x600;

	// Base Combat Entity
	rust_offset BaseCombatEntity_health = 0x224;
	rust_offset BaseCombatEntity_maxHealth = 0x228;
	rust_offset BaseCombatEntity_lifestate = 0x21C;

	// Model State
	rust_offset ModelState_waterLevel = 0x14;
	rust_offset ModelState_flags = 0x24;

	// Player Walk Movement
	rust_offset PlayerWalkMovement_groundAngle = 0xC4;
	rust_offset PlayerWalkMovement_groundAngleNew = 0xC8;
	rust_offset PlayerWalkMovement_groundTime = 0xCC;
	rust_offset PlayerWalkMovement_jumpTime = 0xD0;
	rust_offset PlayerWalkMovement_landTime = 0xD4;
	rust_offset PlayerWalkMovement_grounded = 0x4C;
	rust_offset PlayerWalkMovement_sprinting = 0x40;
	rust_offset PlayerWalkMovement_targetMovement = 0x34;
	rust_offset PlayerWalkMovement_capsuleCenter = 0x6C;

	// Player Model
	rust_offset PlayerModel_newVelocity = 0x22C;
	rust_offset PlayerModel_isLocalPlayer = 0x289;
	rust_offset PlayerModel_MaleSkin = 0x190;
	rust_offset PlayerModel_FemaleSkin = 0x198;
	rust_offset PlayerModel_IsNPC = 0x310;
	rust_offset PlayerModel_visible = 0x278;

	// Player Input
	rust_offset PlayerInput_bodyAngles = 0x3C;
	rust_offset PlayerInput_bodyRotation = 0x2C;

	// Player Eyes
	rust_offset PlayerEyes_viewOffset = 0x38;
	rust_offset PlayerEyes_bodyRotation = 0x44;

	// Projectile
	rust_offset Projectile_drag = 0x24;
	rust_offset Projectile_gravityModifier = 0x28;
	rust_offset Projectile_thickness = 0x2C;

	// Base Projectile
	rust_offset BaseProjectile_automatic = 0x288;
	rust_offset BaseProjectile_canUnloadAmmo = 0x2B4;
	rust_offset BaseProjectile_primaryMagazine = 0x2B8;
	rust_offset BaseProjectile_aimSway = 0x2D0;
	rust_offset BaseProjectile_aimCone = 0x2E8;
	rust_offset BaseProjectile_recoil = 0x2D8;
	rust_offset BaseProjectile_aiming = 0x309;
	rust_offset BaseProjectile_isReloading = 0x324;
	rust_offset BaseProjectile_createdProjectiles = 0x358;

	// Magazine
	rust_offset Magazine_capacity = 0x18;
	rust_offset Magazine_contents = 0x1C;
	rust_offset Magazine_ammoType = 0x20;

	// Recoil Properties
	rust_offset RecoilProperties_recoilYawMin = 0x18;
	rust_offset RecoilProperties_recoilYawMax = 0x1C;
	rust_offset RecoilProperties_recoilPitchMin = 0x20;
	rust_offset RecoilProperties_recoilPitchMax = 0x24;
	rust_offset RecoilProperties_ADSScale = 0x30;
	rust_offset RecoilProperties_movementPenalty = 0x34;

	// Item
	rust_offset Item_info = 0x20;
	rust_offset Item_uid = 0x28;
	rust_offset Item_amount = 0x30;
	rust_offset Item_heldEntity = 0x98;

	// Inventory
	rust_offset Inventory_containerMain = 0x20;
	rust_offset Inventory_containerBelt = 0x28;
	rust_offset Inventory_containerWear = 0x30;
	rust_offset Inventory_crafting = 0x38;
	rust_offset Inventory_loot = 0x40;

	// BaseMountable
	rust_offset BaseMountable_pitchClamp = 0x2A0;
	rust_offset BaseMountable_yawClamp = 0x2A8;
	rust_offset BaseMountable_canWieldItems = 0x2B0;
	rust_offset BaseMountable_canDrinkWhileMounted = 0x308;
}