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

void Bullet::OnUpdate(float dt)
{
	auto tgt = Bug::GetClosestBug(position,
		[position = position](BugBase* b) {return b->position.Distance2(position) < b->GetRadius() * b->GetRadius(); });
	if (tgt != nullptr)
	{
		tgt->visible = false;
		tgt->disabled = true;

		visible = false;
		disabled = true;
	}
}

void Bullet::OnLifeEnd()
{
	visible = false;
	disabled = true;
}
