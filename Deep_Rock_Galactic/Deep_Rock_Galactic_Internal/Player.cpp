#include "Player.h"

void MyPlayer::Start()
{
	Display.SetWindow();
	Display.Print();

	moduleBase = (uintptr_t)GetModuleHandle(L"FSD-Win64-Shipping.exe");
	Shoot = (tShoot)(moduleBase + 0x1514AA0);
	pGameData = (GameData*)Hack::FindDMAAddy(moduleBase + firstOffset, { 0x0, 0x20, 0x0 });
}

void MyPlayer::Validate()
{
	pGameData = (GameData*)Hack::FindDMAAddy(moduleBase + firstOffset, { 0x0, 0x20, 0x0 });

	return;
}

void MyPlayer::Stop()
{
	bSave = true;
	bHasSaved = false;
	savedPoint = { 0 };

	bGoodWeapons = false;
	bGodWeapons = false;
	bRapidFire = false;
	bTeleport = false;
	bSteroids = false;

	pWeaponData = NULL;
	pWeapon = NULL;
	pBody = NULL;

	Display.Print(&Display.sGoodWeapons, "OFF");
	Display.Print(&Display.sGodWeapons, "OFF");
	Display.Print(&Display.sRapidFire, "OFF");
	Display.Print(&Display.sSteroids, "OFF");
	Display.Print(&Display.sTeleport, "NOT SAVED");
}

void MyPlayer::SetBools()
{
	if (!pGameData)
	{
		return;
	}

	if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
		bGoodWeapons = !bGoodWeapons;
		if (bGoodWeapons)
		{
			Display.Print(&Display.sGoodWeapons, "ON");
		}
		else
		{
			Display.Print(&Display.sGoodWeapons, "OFF");

		}
	}

	if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
		bGodWeapons = !bGodWeapons;
		if (bGodWeapons)
		{
			Display.Print(&Display.sGodWeapons, "ON");
		}
		else
		{
			Display.Print(&Display.sGodWeapons, "OFF");

		}
	}

	if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
		bRapidFire = !bRapidFire;
		if (bRapidFire)
		{
			Display.Print(&Display.sRapidFire, "ON");
		}
		else
		{
			Display.Print(&Display.sRapidFire, "OFF");

		}
	}

	if (GetAsyncKeyState(VK_NUMPAD4) & 1) {
		bSteroids = !bSteroids;
		if (bSteroids)
		{
			Display.Print(&Display.sSteroids, "ON");
		}

		else
		{
			Display.Print(&Display.sSteroids, "OFF");

		}
	}

	if (GetAsyncKeyState(VK_NUMPAD7) & 1) {
		bSave = true;
		Teleport();
		Display.Print(&Display.sTeleport, "SAVED");
	}

	if (GetAsyncKeyState(VK_NUMPAD8) & 1) {
		bSave = false;
		Teleport();

	}

}

void MyPlayer::UpdateValues()
{

	Validate();

	if (!pGameData || !pGameData->pPlayerData || pGameData->pPlayerData->BaseHealth == 0)
	{
		Display.Print(&Display.sGameStatus, "WAITING");
		Stop();
		return;
	}

	Display.Print(&Display.sGameStatus, "READY");

	SetBools();

	pWeaponData = pGameData->pWeaponData;
	pWeapon = pWeaponData->pCurrentWeapon;
	pBody = pGameData->pPlayerData->pBody;

	Steroids();


	if (bGoodWeapons)

	{
		GoodWeapons();
	}

	if (bGodWeapons)
	{
		GodWeapons();
	}

	if (bRapidFire)
	{
		RapidFire();
	}


	if (bTeleport)
	{
		Teleport();
	}
}

void MyPlayer::GoodWeapons()
{

	if (!pWeapon)
	{
		return;
	}

	switch (pWeapon->pWeaponType->weaponType)
	{
	case minigun:
	case pistol:
	case zipline:
	case piack_axe:
		pWeapon->ammoSubtraction = -1;
	}

	switch (pWeapon->pWeaponType->weaponType)
	{
	case minigun:
	case pistol:
	case zipline:
		pWeapon->ammo = 1336;
	}

	if (pWeapon->pWeaponType->weaponType == zipline)
	{
		pWeapon->zipLineMaxAngle = 92;
	}


	switch (pWeapon->pWeaponType->weaponType)
	{
	case minigun:
	case pistol:
		pWeapon->recoilX = 0;
		pWeapon->recoilxMag = 0;
		pWeapon->recoilY = 0;
		pWeapon->recoilYMag = 0;
		pWeapon->pStats->spreadMultX = 0;
		pWeapon->pStats->spreadX = 0;
		pWeapon->pStats->spreadMultY = 0;
		pWeapon->pStats->spreadY = 0;
		pWeapon->fireRate = 100;
	}

	pWeaponData->flairs = 4;
	pWeaponData->flairThrowCooldown = 0;

	pWeaponData->pGrenade->grenades = 1338;
}

void MyPlayer::GodWeapons()
{
	if (!pWeapon)
	{
		return;
	}

	switch (pWeapon->pWeaponType->weaponType)
	{
	case minigun:
	case pistol:
		pWeapon->pStats->pWeaponDamage->damage = 1000;
		pWeapon->pStats->pWeaponDamage->fearFactor = 100;
		pWeapon->pStats->pWeaponDamage->stunChance = 100;
		pWeapon->pStats->pWeaponDamage->stunDuraton = 100;
		pWeapon->fireRate = 1000;
	}
}

void MyPlayer::RapidFire()
{
	if (!pWeapon)
	{
		return;
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {

		switch (pWeapon->pWeaponType->weaponType)
		{
		case minigun:
		case pistol:
			Shoot(pWeapon);

		}
	}
}

void MyPlayer::Steroids()
{
	if (!pBody || !pBody->pMovement)
	{
		return;
	}

	if (bSteroids)
	{
		pBody->jumpNumber = 100;
		pBody->pMovement->jumpHeight = 1000;
		pBody->pMovement->pRunSpeed->runSpeed = 1000;
	}
	else
	{
		pBody->jumpNumber = 1;
		pBody->pMovement->jumpHeight = 500;
		pBody->pMovement->pRunSpeed->runSpeed = 450;
	}
}

void MyPlayer::Teleport()
{
	if (!pBody || !pBody->pMovement)
	{
		return;
	}

	if (!bSave) {
		if (!bHasSaved)
		{
			return;
		}

		pBody->pMovement->pPosition->position.x = savedPoint.x;
		pBody->pMovement->pPosition->position.y = savedPoint.y;
		pBody->pMovement->pPosition->position.z = savedPoint.z;

		return;
	}


	savedPoint.x = pBody->pMovement->pPosition->position.x;
	savedPoint.y = pBody->pMovement->pPosition->position.y;
	savedPoint.z = pBody->pMovement->pPosition->position.z;

	bHasSaved = true;
}