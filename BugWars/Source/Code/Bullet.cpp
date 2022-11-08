#include "pch.h"
#include "Bullet.h"
#include "Game.h"
#include "Bug.h"
#include "Tank.h"

IMPLEMENT_RTTI(Bullet);

Bullet::Bullet()
{
	disabled = false;
	visible = true;
}

void Bullet::OnStart(Point)
{
}

//void Bullet::OnUpdate(float dt)
//{
//	for (int r = 0; r <= 3 * 3 / CHUNK_SIZE; r++)
//	{
//		for (int i = -r; i <= r; i++)
//			for (int j = std::abs(i) - r; j <= r - std::abs(i); j++)
//				if (std::abs(i) + std::abs(j) == r 
//					&& g_Game->mapChunks.contains(std::pair((int)position.x / CHUNK_SIZE + i, (int)position.x / CHUNK_SIZE + j)) )
//				{
//					auto vec = g_Game->mapChunks[std::pair(i, j)];
//					for (auto object : vec)
//						if (object->position.Distance(position) < object->GetRadius())
//							if (!object->disabled)
//								if (object->GetRTTI() == Bug::s_RTTI)
//								{
//									g_Game->tank->score++;
//									object->visible = false;
//									object->disabled = true;
//
//									visible = false;
//									disabled = true;
//									return;
//								}
//				}
//	}
//}

void Bullet::OnUpdate(float dt)
{
	for (auto object : g_Game->objects)
		if (!object->disabled)
			if (object->position.Distance(position) < object->GetRadius())
				if (object->GetRTTI() == Bug::s_RTTI)
				{
					g_Game->tank->score++;
					object->visible = false;
					object->disabled = true;
		
					visible = false;
					disabled = true;
					return;
				}
}

void Bullet::OnLifeEnd()
{
	visible = false;
	disabled = true;
}
