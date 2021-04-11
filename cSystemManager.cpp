#include "DXUT.h"
#include "cSystemManager.h"


cSystemManager::cSystemManager()
{
}


cSystemManager::~cSystemManager()
{
}

void cSystemManager::Init()
{
	m_Debug = false;
	m_ComboScale = 1;
	m_Player[0] = nullptr;
	m_Player[1] = nullptr;
	m_PlayerRemain = 0;

	m_Ranking.push_back(Rank{ L"HRK", 10000000 });
	m_Ranking.push_back(Rank{ L"CHY", 8000000 });
	m_Ranking.push_back(Rank{ L"MKI", 6000000 });
	m_Ranking.push_back(Rank{ L"MKT", 4000000 });
	m_Ranking.push_back(Rank{ L"YKH", 2000000 });

	SortRank();
}

void cSystemManager::Update()
{
	m_NSDT = DXUTGetElapsedTime();

	m_DT = m_NSDT * m_TimeScale;

	for (int i = 0; i < 5; i++)
	{
		m_Alarm[i] -= m_NSDT;
		if (m_Alarm[i] <= 0)
		{
			m_Alarm[i] = 100000;
			switch (i)
			{
			case 0:
				m_TimeScale = 1;
				break;
				
			case 1:
				m_ComboEnded = true;
				break;

			case 2:
				if (m_ComboEnded == true)
				{
					m_Combo = 0;
				}
				break;
			}
		}
	}

	if (m_Player[0] != nullptr)
	{
		cCharacter* Player = m_Player[0]->GC(cCharacter);

		if (m_ComboEnded == true)
		{
			if ((Player->m_MainState == State_Hit || Player->m_MainState == State_Down || Player->m_MainState == State_Idle) && m_Alarm[2] > 100)
			{
				m_Alarm[2] = 1;
			}
		}

		if (INPUT->KeyDown(VK_F1))
		{
			Player->m_Invincible = !Player->m_Invincible;
		}
	}

	if (INPUT->KeyDown(VK_F7))
	{
		m_Debug = !m_Debug;
	}

	m_ComboScale = Lerp<float>(m_ComboScale, 1, 0.15);
}

void cSystemManager::Render()
{
	TCHAR Text[32];
	//if (OBJECT->m_Player != nullptr)
	//{
	//	cCharacter* Player = OBJECT->m_Player->GC(cCharacter);

	//	if (m_Combo != 0)
	//	{
	//		IMAGE->CenterRender(IMAGE->Find("Combo"), Vec2(200, 400), Vec2(4, 4) * m_ComboScale, 0, 0.1, 0xffffffff, true);
	//		char Temp[16];
	//		string Combo = to_string(m_Combo);
	//		if (Combo.size() == 1)
	//		{
	//			IMAGE->CenterRender(m_ComboNumber[Combo[0] - '0'], Vec2(200, 400), Vec2(4, 4) * m_ComboScale, 0, 0.1, 0xffffffff, true);
	//		}
	//		else if (Combo.size() == 2)
	//		{
	//			IMAGE->CenterRender(m_ComboNumber[Combo[0] - '0'], Vec2(200 - 35 * m_ComboScale, 400), Vec2(4, 4) * m_ComboScale, 0, 0.1, 0xffffffff, true);
	//			IMAGE->CenterRender(m_ComboNumber[Combo[1] - '0'], Vec2(200 + 35 * m_ComboScale, 400), Vec2(4, 4) * m_ComboScale, 0, 0.1, 0xffffffff, true);
	//		}
	//		else
	//		{
	//			IMAGE->CenterRender(m_ComboNumber[Combo[0] - '0'], Vec2(200 - 70 * m_ComboScale, 400), Vec2(4, 4) * m_ComboScale, 0, 0.1, 0xffffffff, true);
	//			IMAGE->CenterRender(m_ComboNumber[Combo[1] - '0'], Vec2(200, 400), Vec2(4, 4) * m_ComboScale, 0, 0.1, 0xffffffff, true);
	//			IMAGE->CenterRender(m_ComboNumber[Combo[2] - '0'], Vec2(200 + 70 * m_ComboScale, 400), Vec2(4, 4) * m_ComboScale, 0, 0.1, 0xffffffff, true);
	//		}
	//	}

	//}
	//float Scale = 5;
	//if (OBJECT->m_Boss != nullptr)
	//{
	//	cCharacter* Boss = OBJECT->m_Boss->GC(cCharacter);
	//	IMAGE->Render(IMAGE->Find("HpBar2_Under"), Vec2(1910, 10), Vec2(-Scale, Scale), 0, 0.1, 0xffffffff, true);
	//	IMAGE->Render(IMAGE->Find("HpBar_Hp"), Vec2(1910 + 31 * -Scale, 10), Vec2(Clamp(Boss->m_Hp / Boss->m_MaxHp, 0, 1) * -Scale * 104, Scale), 0, 0.1, 0xffffffff, true);
	//	IMAGE->Render(IMAGE->Find("HpBar_Stun"), Vec2(1910 + 53 * -Scale, 10), Vec2(Clamp(Boss->m_Stun / Boss->m_MaxStun, 0, 1) * -Scale * 78, Scale), 0, 0.1, 0xffffffff, true);
	//	IMAGE->Render(IMAGE->Find("HpBar2_Upper"), Vec2(1910, 10), Vec2(-Scale, Scale), 0, 0.1, 0xffffffff, true);
	//	IMAGE->Render(IMAGE->Find(Boss->m_Owner->m_Name == "Iori" ? "HpBar_Port_Iori" : "HpBar_Port_Rugal"), Vec2(1910, 10), Vec2(-Scale, Scale), 0, 0.1, 0xffffffff, true);
	//}
}

void cSystemManager::Release()
{
}

void cSystemManager::PlayerInit()
{
	m_Score = 0;
	m_Combo = 0;
	m_ComboEnded = true;
	m_Win = false;
	char Text[32];
	for (int i = 0; i < 10; i++)
	{
		sprintf(Text, "Combo_Number%d", i);
		m_ComboNumber[i] = IMAGE->Find(Text);
		sprintf(Text, "Damage_Number%d", i);
		m_DamageNumber[i] = IMAGE->Find(Text);
	}
}

void cSystemManager::SortRank()
{
	m_Ranking.sort([&](Rank _Prev, Rank _Next)->bool {return _Prev.Score > _Next.Score; });
}

void cSystemManager::HitStop(float _Time, float _Speed)
{
	m_TimeScale = _Speed;
	m_Alarm[0] = m_PlayerRemain == 1 ? _Time : _Time * 0.5f;
}
