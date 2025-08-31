#ifndef GENCODE_H
#define GENCODE_H
#include "geom.h"



class Player
{
public:
	char pad_0000[4]; //0x0000
	Vector3 axis; //0x0004
	Vector3 velocity; //0x0010
	Vector3 N00000053; //0x001C
	Vector3 pos; //0x0028
	float yaw; //0x0034
	float pitch; //0x0038
	float roll; //0x003C
	char pad_0040[16]; //0x0040
	float eyeheight; //0x0050
	float headheight; //0x0054
	char pad_0058[148]; //0x0058
	int32_t health; //0x00EC
	char pad_00F0[236]; //0x00F0
	int32_t kills; //0x01DC
	char pad_01E0[37]; //0x01E0
	char name[104]; //0x0205
	char pad_026D[159]; //0x026D
	int8_t team; //0x030C


}; 

class EntityList {
public:
	Player* players[64];
};

#endif // GENCODE_H