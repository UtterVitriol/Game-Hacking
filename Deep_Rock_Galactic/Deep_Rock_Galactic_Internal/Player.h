#pragma once

#include "GameData.h"
#include "Hack.h"
#include "Display.h"

#include <vector>

class MyPlayer
{
public:
	void Start();
	void Validate();
	void Stop();
	void SetBools();
	void UpdateValues();
	uintptr_t moduleBase = 0;
	uint32_t firstOffset = 0x61E2200;
	std::vector<unsigned int> offsets = { 0x0, 0x20, 0x0 };
	GameData* pGameData = NULL;

	uintptr_t check = 0;
	uintptr_t oldcheck = 0;
	std::vector<unsigned int> validateOffsets = { 0x0 };


private:
	void GoodWeapons();
	void GodWeapons();
	void RapidFire();
	void Steroids();
	void Teleport();

	TrainerDisplay Display;

	WeaponData* pWeaponData = NULL;
	Weapon* pWeapon = NULL;
	Body* pBody = NULL;


	typedef void (*tShoot)(Weapon*);
	tShoot Shoot = nullptr;

	bool bSave = true;
	bool bHasSaved = false;
	Vec3 savedPoint = { 0 };

	bool bGoodWeapons = false;
	bool bGodWeapons = false;
	bool bRapidFire = false;
	bool bSteroids = false;
	bool bTeleport = false;


};

