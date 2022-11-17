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
	for (auto it = objects.end() - 1; it != objects.begin() - 1; it--)
	{
		auto obj = *it;
		if (!obj->disabled)
		{
			obj->Update(dt);
		}
		else
		{
			to_del.emplace_back(obj);
			objects.erase(it);
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
}

std::pair<int, int> Game::GetObjectChunk(GameObject* object)
{
	return std::pair<int, int>(((int)object->position.x) / CHUNK_SIZE, ((int)object->position.y)/ CHUNK_SIZE);
}

void Game::OnBugsSpawned()
{
}