#include "DXUT.h"
#include "cStage1Scene.h"
#include "cKyo.h"
#include "cKim.h"
#include "cIori_Player.h"
#include "cRobert.h"
#include "cRalf.h"
#include "cDuck.h"
#include "cBig.h"
#include "cIori.h"
#include "cRugal.h"
#include "cGround.h"

cStage1Scene::cStage1Scene()
{
}


cStage1Scene::~cStage1Scene()
{
}

void cStage1Scene::Init()
{
	cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Point"), Vec2(0, 0), Vec2(10000, 10000), 0, 0, 0, 0xff000000);
	Part->SetAlpha(255, -255, 1);

	SOUND->Play("BGM_Stage1", 0, true);
	m_CameraMin = 500;
	m_CameraMax = 2500;
	CAMERA->m_Pos = Vec2(480, -200);
	CAMERA->SetScale(2);
	m_Phase = 0;

	for (int i = 0; i < 2; i++)
	{
		switch (m_Characters[i])
		{
			case Char_Kyo: OBJECT->AddObject("Kyo", Vec2(i == 0 ? 1200 : 1800, -50), 75, 0.5, Obj_Player)->AC(cKyo)->SetSide(i); break;
			case Char_Kim: OBJECT->AddObject("Kim", Vec2(i == 0 ? 1200 : 1800, -50), 75, 0.5, Obj_Player)->AC(cKim)->SetSide(i); break;
			case Char_Iori: OBJECT->AddObject("Iori_Player", Vec2(i == 0 ? 1200 : 1800, -50), 75, 0.5, Obj_Player)->AC(cIori_Player)->SetSide(i); break;
		}
	}
	m_Player = SYSTEM->m_Player[0] == nullptr ? 1 : 0;

	cObject* a = OBJECT->AddObject("Ground", Vec2(0, 0), 0, 0, Obj_Map);
	a->AC(cGround)->Setting(Vec2(1000000, 1000000), Vec2(0, 1000000), 10000);

	if (SYSTEM->m_GameMode != GM_PvP)
	{
		SCHEDULE->AddSchedule(0, true, [&]()->bool {
			if (m_Phase != 15)
			{
				switch (Random(0, 4))
				{
				case 0: OBJECT->AddObject("Robert", Vec2(Random(0, 1) == 0 ? 400 : 2600, -50), Random(0, 150), 0.5, Obj_Enemy)->AC(cRobert); break;
				case 1: OBJECT->AddObject("Ralf", Vec2(Random(0, 1) == 0 ? 400 : 2600, -50), Random(0, 150), 0.5, Obj_Enemy)->AC(cRalf); break;
				case 2: OBJECT->AddObject("Big", Vec2(Random(0, 1) == 0 ? 400 : 2600, -50), Random(0, 150), 0.5, Obj_Enemy)->AC(cBig); break;
				case 3: OBJECT->AddObject("Duck", Vec2(Random(0, 1) == 0 ? 400 : 2600, -50), Random(0, 150), 0.5, Obj_Enemy)->AC(cDuck); break;
				}
				m_Phase++;
			}
			else
			{
				switch (Random(0, 2))
				{
				case 0: OBJECT->AddObject("Iori", Vec2(Random(0, 1) == 0 ? 400 : 2600, -50), Random(0, 150), 0.5, Obj_Enemy)->AC(cIori); break;
				case 1: OBJECT->AddObject("Rugal", Vec2(Random(0, 1) == 0 ? 400 : 2600, -70), Random(0, 150), 0.5, Obj_Enemy)->AC(cRugal); break;
				}
				m_Phase = 0;
			}
			AddEnemy();
			return true;
		});
	}
}

void cStage1Scene::Update()
{
	if (SYSTEM->m_PlayerRemain != 0)
	{
		Vec2 Pos = SYSTEM->m_PlayerRemain == 1 ? (SYSTEM->m_Player[m_Player]->GC(cCharacter)->m_Dead ? SYSTEM->m_Player[!m_Player]->m_Pos : SYSTEM->m_Player[m_Player]->m_Pos) : (SYSTEM->m_Player[0]->m_Pos + SYSTEM->m_Player[1]->m_Pos) * 0.5f;
		Pos.y = Clamp(Pos.y, -500, -150);
		CAMERA->m_Pos = Lerp<Vec2>(CAMERA->m_Pos, Pos, 0.1);
	}
	CAMERA->m_Pos = Vec2(Clamp(CAMERA->m_Pos.x, m_CameraMin + 960 / CAMERA->m_Scale, m_CameraMax - 960 / CAMERA->m_Scale), CAMERA->m_Pos.y);
}

void cStage1Scene::Render()
{
	IMAGE->Render(IMAGE->Find("Stage1_Back"), Vec2(-50, -1000), Vec2(2, 2), 0, 0.9);
}

void cStage1Scene::Release()
{
}

void cStage1Scene::AddEnemy()
{
	if (SYSTEM->m_GameMode == GM_PvP)
		return;
	float Time = (SYSTEM->m_Player[0] != nullptr && SYSTEM->m_Player[1] != nullptr) ? 6 : 9;
	if (SYSTEM->m_GameMode == GM_PvPvE)
		Time *= 2;
	SCHEDULE->AddSchedule(Time, true, [&]()->bool {
		if (m_Phase != 15)
		{
			if (OBJECT->m_Objects[Obj_Enemy].size() >= 10)
			{
				AddEnemy();
				return true;
			}
			switch (Random(0, 3))
			{
			case 0: OBJECT->AddObject("Robert", Vec2(Random(0, 1) == 0 ? -100 : 4100, -50), 75, 0.5, Obj_Enemy)->AC(cRobert); break;
			case 1: OBJECT->AddObject("Ralf", Vec2(Random(0, 1) == 0 ? -100 : 4100, -50), 75, 0.5, Obj_Enemy)->AC(cRalf); break;
			case 2: OBJECT->AddObject("Big", Vec2(Random(0, 1) == 0 ? -100 : 4100, -50), 75, 0.5, Obj_Enemy)->AC(cBig); break;
			case 3: OBJECT->AddObject("Duck", Vec2(Random(0, 1) == 0 ? -100 : 4100, -50), 75, 0.5, Obj_Enemy)->AC(cDuck); break;
			}
			m_Phase++;
			AddEnemy();
		}
		else
		{
			switch (Random(0, 1))
			{
			case 0: OBJECT->AddObject("Iori", Vec2(Random(0, 1) == 0 ? -100 : 4100, -50), 75, 0.5, Obj_Enemy)->AC(cIori); break;
			case 1: OBJECT->AddObject("Rugal", Vec2(Random(0, 1) == 0 ? -100 : 4100, -70), 75, 0.5, Obj_Enemy)->AC(cRugal); break;
			}
			m_Phase = 0;
		}
		return true;
	});
}
