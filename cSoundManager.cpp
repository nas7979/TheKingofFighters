#include "DXUT.h"
#include "cSoundManager.h"


cSoundManager::cSoundManager()
{
}


cSoundManager::~cSoundManager()
{
}

void cSoundManager::Init()
{
	m_Manager.Initialize(DXUTGetHWND(), 1);
}

void cSoundManager::Update()
{
	DWORD Status;
	for (auto& iter = m_Channels.begin(); iter != m_Channels.end();)
	{
		(*iter)->GetStatus(&Status);
		if ((Status & DSBSTATUS_PLAYING) == false)
		{
			(*iter)->Release();
			iter = m_Channels.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	m_Played.clear();
}

void cSoundManager::Render()
{
}

void cSoundManager::Release()
{
	for (auto& iter : m_Sounds)
	{
		delete iter.second;
	}
	StopAll();
}

void cSoundManager::AddSound(string _Key, string _Path)
{
	CSound* a;
	wstring Path;
	Path.assign(_Path.begin(), _Path.end());
	m_Manager.Create(&a,  (LPWSTR)Path.c_str(), DSBCAPS_CTRLVOLUME);
	m_Sounds.insert(make_pair(_Key, a));
}

LPDIRECTSOUNDBUFFER cSoundManager::Play(string _Key, long _Volume, bool _Loop, bool _IsVoice)
{
	LPDIRECTSOUNDBUFFER a;
	m_Manager.GetDirectSound()->DuplicateSoundBuffer(m_Sounds[_Key]->GetBuffer(0), &a);
	a->Play(0, 0, _Loop ? DSBPLAY_LOOPING : 0);
	if(_IsVoice == false)
		m_Channels.push_back(a);
	for (auto& iter : m_Played)
	{
		if (iter == _Key)
		{
			a->Stop();
			return a;
		}
	}
	m_Played.push_back(_Key);
	a->SetVolume(_Volume);
	return a;  
}

void cSoundManager::StopAll()
{
	for (auto& iter : m_Channels)
	{
		iter->Release();
	}
	m_Channels.clear();
}
