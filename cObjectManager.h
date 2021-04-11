#pragma once
#include "cObject.h"
class cObjectManager : public cSingleton<cObjectManager>
{
public:
	cObjectManager();
	~cObjectManager();

	void Init();
	void Update();
	void Render();
	void Release();

	list<cObject*> m_Objects[Obj_End];
	cObject* m_Boss = nullptr;

	cObject* AddObject(string _Name, Vec2 _Pos, float _Z, float _Depth, ObjectTag _Tag);
	void CheckCollision(cObject* _Object);
};

#define OBJECT cObjectManager::GetInstance()