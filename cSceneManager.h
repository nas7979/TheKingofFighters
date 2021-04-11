#pragma once
#include "cScene.h"
class cSceneManager : public cSingleton<cSceneManager>
{
public:
	cSceneManager();
	~cSceneManager();

	void Init();
	void Update();
	void Render();
	void Release();

	map<string, cScene*> m_Scenes;
	cScene* m_Cur = nullptr;
	cScene* m_New = nullptr;

	void AddScene(string _Key, cScene* _Scene);
	void ChangeScene(string _Key);
};

#define SCENE cSceneManager::GetInstance()