#include "pch.h"
#include "Bug.h"
#include "Game.h"

IMPLEMENT_RTTI(Bug);

Bug::Bug()
{
	disabled = false;
	visible = true;
}

void Bug::OnUpdate(float dt)
{
}

BugBase* Bug::FindBugToEat() const
{
	return GetClosestBug(position, [id = id](BugBase* b) {return b->id < id; });
}

void Bug::OnEat(BugBase& first, BugBase& second)
{
	BugBase* dead;
	if (first.id > second.id)
	{
		dead = &second;
	}
	else
	{
		dead = &first;
	}

	dead->visible = false;
	dead->disabled = true;
}
