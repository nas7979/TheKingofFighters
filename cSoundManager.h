#pragma once
class cSoundManager : public cSingleton<cSoundManager>
{
public:
	cSoundManager();
	~cSoundManager();

	void Init();
	void Update();
	void Render();
	void Release();

	map<string, CSound*> m_Sounds;
	list<LPDIRECTSOUNDBUFFER> m_Channels;
	vector<string> m_Played;
	CSoundManager m_Manager;

	void AddSound(string _Key, string _Path);
	LPDIRECTSOUNDBUFFER Play(string _Key, long _Volume, bool _Loop = false, bool _IsVoice = false);
	void StopAll();
};

#define SOUND cSoundManager::GetInstance()