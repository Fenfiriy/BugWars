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
	Bug* target = nullptr;
	float min_dist = std::numeric_limits<float>::max();
	for (auto object : g_Game->objects)
	{
		if (object->id >= id)
			continue; // Can't eat that

		if (object->disabled)
			continue;

		if (object->GetRTTI() == Bug::s_RTTI)
		{
			float dist = position.Distance(object->position);
			if (dist < min_dist)
			{
				min_dist = dist;
				target = dynamic_cast<Bug*>(object);
			}
		}
	}

	return target;
}

void Bug::OnEat(BugBase& first, BugBase& second)
{
	if (first.id > second.id)
	{
		second.visible = false;
		second.disabled = true;
	}
	else
	{
		first.visible = false;
		first.disabled = true;
	}
}
