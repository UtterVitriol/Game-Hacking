#pragma once

typedef struct Vector3{ float x, y, z; }Vec3;

// Created with ReClass.NET 1.2 by KN4CK3R

class PlayerHealth
{
public:
	char pad_0000[124]; //0x0000
	float N00000063; //0x007C
	char pad_0080[44]; //0x0080
	float Health; //0x00AC
	char pad_00B0[1996]; //0x00B0
}; //Size: 0x087C
static_assert(sizeof(PlayerHealth) == 0x87C);

class PlayerBody
{
public:
	char pad_0000[48]; //0x0000
	Vec3 notPos; //0x0030
	char pad_003C[260]; //0x003C
	Vec3 notPos2; //0x0140
	char pad_014C[60]; //0x014C
	float faceOne1; //0x0188
	float faceTwo1; //0x018C
	float faceThree1; //0x0190
	float faceThree2; //0x0194
	float faceOne2; //0x0198
	float faceTwo2; //0x019C
	Vec3 position; //0x01A0
	char pad_01AC[20]; //0x01AC
	Vec3 velocity; //0x01C0
	char pad_01CC[208]; //0x01CC
	float stepHeight; //0x029C
	char pad_02A0[24]; //0x02A0
	float speed; //0x02B8
	char pad_02BC[1488]; //0x02BC
}; //Size: 0x088C
static_assert(sizeof(PlayerBody) == 0x88C);