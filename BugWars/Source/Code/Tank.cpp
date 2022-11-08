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

//BugBase* Tank::GetBugToShoot() const
//{
//	for (int r = 0; r <= 1000 * 3 / CHUNK_SIZE; r++)
//	{
//		for (int i = -r; i <= r; i++)
//			for (int j = std::abs(i) - r; j <= r - std::abs(i); j++)
//				if (std::abs(i) + std::abs(j) == r
//					&& g_Game->mapChunks.contains(std::pair((int)position.x / CHUNK_SIZE + i, (int)position.x / CHUNK_SIZE + j)))
//				{
//					auto vec = g_Game->mapChunks[std::pair(i, j)];
//					for (auto obj : vec)
//					{
//						if (obj->disabled)
//							continue;
//						if (obj->GetRTTI() == Bug::s_RTTI)
//						{
//							if (obj->position.Distance(position) < 200.0f)
//								return dynamic_cast<Bug*>(obj);
//						}
//					}
//				}
//	}
//	return nullptr;
//}

BugBase* Tank::GetBugToShoot() const
{
	float min_dist = std::numeric_limits<float>::max();
	BugBase* res = nullptr;

	for (auto obj : g_Game->objects)
	{
		if (obj->disabled)
			continue;
		if (obj->GetRTTI() == Bug::s_RTTI)
		{
			if (obj->position.Distance(position) < min_dist)
			{
				min_dist = obj->position.Distance(position);
				res = dynamic_cast<Bug*>(obj);
			}
		}
	}

	return res;
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
