#include "pch.h"
#include "Game.h"
#include "GameBase/Log.h"
#include "Tank.h"
#include "Bug.h"
#include "Bullet.h"

Game* g_Game;
template <typename T>
T* enabl(T* go)
{
	go->disabled = false;
	return go;
}

Game::Game()
	: GameBase({ [] {return enabl(new Tank); },
				 [] {return enabl(new Bug); },
				 [] {return enabl(new Bullet); }})
{
	g_Game = this;
}

Game::~Game()
{
	for (auto obj : objects)
		delete(obj);
}

void Game::OnUpdate(float dt)
{
	PIXScopedEvent(PIX_COLOR_INDEX(5), __FUNCTION__);
	std::vector<GameObject*> to_del;
	for (int i = 0; i < objects.size(); i++)
	{
		auto obj = objects[i];
		if (!obj->disabled)
		{
			obj->Update(dt);
		}
		else
		{
			to_del.emplace_back(obj);
			objects[i] = objects[objects.size() - 1];
			objects.pop_back();
		}
	}

	for (auto ob : to_del)
		delete(ob);
}

void Game::OnRender() const
{
	for (auto obj : objects)
		if (obj->visible)
			DoRender(obj);
}

void Game::AddObject(GameObject* object)
{
	objects.push_back(object);

	//mapChunks[std::pair<int, int>((int)object->position.x / CHUNK_SIZE, (int)object->position.y / CHUNK_SIZE)].push_back(object);
	/*if (object->GetRTTI() == Bug::s_RTTI)
		LogZA("I'm a bug %i", object->id);*/
}

void Game::OnBugsSpawned()
{
}
