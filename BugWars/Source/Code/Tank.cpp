#include "pch.h"
#include "Tank.h"
#include "Globals.h"
#include "Game.h"
#include "Bullet.h"
#include "Bug.h"

#include "GameBase/Log.h"

IMPLEMENT_RTTI(Tank);

Tank::Tank()
{
	disabled = false;
	visible = true;
}

void Tank::OnUpdate(float dt)
{
}

BugBase* Tank::GetBugToShoot() const
{
	return Bug::GetClosestBug(position, [](BugBase* b) {return true; });
}

Point Tank::CalcShootDirection(Point target_pos, Point target_dir, float target_vel, float bullet_vel) const
{
	Point resultDir = {1, 0};
	Point r1 = (position * target_vel + target_pos * bullet_vel) / (target_vel + bullet_vel);
	Point r2 = (target_pos * bullet_vel - position * target_vel) / (bullet_vel - target_vel);
	Point center = (r1 + r2) * 0.5f;
	float radius2 = r1.Distance2(r2) * 0.25f;

	float b = target_dir.Dot(target_pos - center);
	float c = (target_pos - center).Length2() - radius2;

	float alpha = -b + sqrtf(b * b - c);
	resultDir = (target_pos + target_dir * alpha - position).Normalized();
	return resultDir;
}
