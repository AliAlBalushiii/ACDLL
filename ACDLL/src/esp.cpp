#include "esp.h"
#include "constants.h"
#include <stdio.h>
#include <iostream>
#include "geom.h"
#include "settings.h"
#include "imgui.h"
const float Fov = 90;

void normalizeAngle(vec3& angle) {
	if (angle.x > 360)
	{
		angle.x -= 360;
	}
	if (angle.x < 0)
	{
		angle.x += 360;
	}
	if (angle.y > 90)
	{
		angle.y -= 90;
	}
	if (angle.y < -90)
	{
		angle.y += 90;
	}
}

bool isInFov(Player* owner, Vec3 looking) {
	vec3 angle = CalcAngle(owner->pos, looking);
	vec3 playerAngle{ owner->yaw + 180, owner->pitch, 0 };
	normalizeAngle(playerAngle);

	vec3 angleDiff = playerAngle - angle;
	normalizeAngle(angleDiff);

	return (fabs(angleDiff.x) <= Fov / 2 && fabs(angleDiff.y) <= Fov / 2);
}

bool isValidTarget(Player* player) {
	if (player->health > 100 || player->health < 0 || !isInFov(playerclass, player->axis))
		return false;
	return true;
}

Player* ESP::getNearestPlayer() {
	Player* nearstPlayer = nullptr;
	float nearestDistance = 999999.0f;

	for (int i = 1; i <= amount; i++) {
		Player* player = players->players[i];
		if (!isValidTarget(player))
			continue;
		float distance = playerclass->pos.Distance(player->pos);
		if (distance < nearestDistance)
		{
			nearestDistance = distance;
			nearstPlayer = player;
		}
	}
	return nearstPlayer;
}	

Player* ESP::getNearestEntityAngle() {
	vec3 playerAngle{ playerclass->yaw + 180, playerclass->pitch,0 };
	normalizeAngle(playerAngle);
	Player* nearestPlayer = nullptr;
	float smallestAngle = 9999999.0f;

	for (int i = 1; i <= amount; i++) {
		Player* player = players->players[i];
		if (!isValidTarget(player))
			continue;
		vec3 targetAngle = CalcAngle(playerclass->pos, player->pos);
		vec3 angleDiff = playerAngle - targetAngle;
		normalizeAngle(angleDiff);
		float angleMagnitue = angleDiff.Length();
		if (angleMagnitue < smallestAngle) {
			smallestAngle = angleMagnitue;
			nearestPlayer = player;
		}
		{

		}
	}
	return nearestPlayer;
}

void ESP::aimbot() {
	if (!GetAsyncKeyState(VK_SHIFT))
		return;
	Player* target = getNearestEntityAngle();
	if (!target)
		return;
	Vec3 angel = CalcAngle(playerclass->pos, target->pos);
	angel.x += 180; // Adjust yaw to face the target
	playerclass->yaw = angel.x;
	playerclass->pitch = angel.y;
}

void ESP::drawESP() {
	bool teammate = false;
	Player* player = nullptr;
	for (int i = 1; i <= amount; i++)
	{
		player = players->players[i];
		if (player->health > 100 || player->health <=0)
		{
			continue;
		}
		teammate = player->team == playerclass->team;
		if (teammate && !Settings::ESP::drawTeam)
		{
			continue;
		}
		vec3 headPos = { player->axis.x, player->axis.y, player->axis.z};
		vec3 headPos = { player->axis.x, player->axis.y, player->axis.z - player->eyeheight};
		vec3 headScreenPos = 
	}
}
