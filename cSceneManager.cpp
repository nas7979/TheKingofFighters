#include "DXUT.h"
#include "cSceneManager.h"


cSceneManager::cSceneManager()
{
}


cSceneManager::~cSceneManager()
{
}

void cSceneManager::Init()
{
}

void cSceneManager::Update()
{
	if (m_New)
	{
		OBJECT->Release();
		PART->Release();
		SOUND->StopAll();
		SCHEDULE->Release();
		SYSTEM->m_TimeScale = 1;
		if (m_Cur)
			m_Cur->Release();
		m_Cur = m_New;
		m_New = nullptr;
		m_Cur->Init();
	}
	if (m_Cur)
	{
		m_Cur->Update();
	}
}

void cSceneManager::Render()
{
	if (m_Cur)
	{
		m_Cur->Render();
	}
}

void cSceneManager::Release()
{
	for (auto& iter : m_Scenes)
	{
		iter.second->Release();
		delete iter.second;
	}
}

void cSceneManager::AddScene(string _Key, cScene * _Scene)
{
	m_Scenes.insert(make_pair(_Key, _Scene));
}

void cSceneManager::ChangeScene(string _Key)
{
	m_New = m_Scenes[_Key];
}
