#pragma once
#include "GameBase/GameBase.h"
#include "Globals.h"

#define CHUNK_SIZE 256
struct Tank;

struct Game : public GameBase
{
	Game();
	~Game();

	virtual void OnUpdate(float dt) override;
	virtual void OnRender() const override;
	virtual void AddObject(GameObject* object) override;

	std::pair<int, int> GetObjectChunk(GameObject* object);

	virtual void OnBugsSpawned() override;

	std::vector<GameObject*> objects;

};