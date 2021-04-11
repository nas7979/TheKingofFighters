#pragma once
#include "cSingleton.h"
class cRenderer;
class cObject;
enum Skill {
	Skill_Aragami1,
	Skill_Aragami2,
	Skill_Kai1,
	Skill_Kai2,
	Skill_Oniyaki1,
	Skill_Oniyaki2,
	Skill_Body1,
	Skill_Body2,
	Skill_Body3,
	Skill_End
};
enum GameMode
{
	GM_PvE,
	GM_PvP,
	GM_PvPvE
};
struct Rank
{
	wstring Name;
	int Score;
};
class cSystemManager : public cSingleton<cSystemManager>
{
public:
	cSystemManager();
	~cSystemManager();

	void Init();
	void Update();
	void Render();
	void Release();

	float m_DT;
	float m_NSDT;
	int m_Score;
	int m_Combo;
	bool m_ComboEnded;
	bool m_Win;
	float m_TimeScale;
	float m_Alarm[5];
	bool m_Debug;
	list<Rank> m_Ranking;
	Texture* m_ComboNumber[10];
	Texture* m_DamageNumber[10];
	float m_ComboScale;
	cObject* m_Player[2];
	int m_PlayerRemain;
	GameMode m_GameMode;

	void PlayerInit();
	void SortRank();
	void HitStop(float _Time, float _Speed = 0.1);
};

#define SYSTEM cSystemManager::GetInstance()