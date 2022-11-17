#pragma once
#include "GameBase/BugBase.h"
#include "Game.h"

struct Bug : public BugBase
{
	DEFINE_RTTI;
	Bug();
	virtual void OnUpdate(float dt) override;
	virtual BugBase* FindBugToEat() const override;
	virtual void OnEat(BugBase& first, BugBase& second) override;

public:
	template <typename UnaryPredicate>
	static Bug* GetClosestBug(Point p, UnaryPredicate cond)
	{
		Bug* target = nullptr;
		float min_dist = std::numeric_limits<float>::max();
		auto objects = g_Game->objects;
		for (auto it = --objects.end(); it != --objects.begin(); it--)
		{
			auto object = *it;
			if (object->GetRTTI() == Bug::s_RTTI && !(object->disabled))
			{
				auto stf = static_cast<Bug*>(object);
				if (cond(stf))
				{
					float dist = p.Distance2(stf->position);
					if (dist < min_dist)
					{
						min_dist = dist;
						target = stf;
					}
				}
			}
		}
						

		return target;
	}
};
