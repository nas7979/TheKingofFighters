#include "DXUT.h"
#include "cSelectScene.h"
#include "cStage1Scene.h"


cSelectScene::cSelectScene()
{
}


cSelectScene::~cSelectScene()
{
}

void cSelectScene::Init()
{
	m_CharacterAmount = 3;
	m_ModeSelected = 0;

	cObject* a;
	for (int Side = -1; Side <= 1; Side += 2)
	{
		for (int i = 0; i < m_CharacterAmount; i++)
		{
			a = OBJECT->AddObject("Player", Vec2(960 + 600 * Side, 600), 0, 0.1, Obj_None);
			m_Characters[Side == -1 ? 0 : 1].push_back(a);
			m_Characters[Side == -1 ? 0 : 1][i]->m_Scale.x = -Side;
		}
		m_Characters[Side == -1 ? 0 : 1][0]->AC(cAnimation)->AddAnimation("Kyo_Idle", "Kyo_Idle", 0.1f);
		m_Characters[Side == -1 ? 0 : 1][0]->GC(cAnimation)->AddAnimation("Kyo_Ready", "Kyo_Ready", 0.0275f, false);
		m_Characters[Side == -1 ? 0 : 1][0]->GC(cAnimation)->SetAnimation("Kyo_Idle");

		m_Characters[Side == -1 ? 0 : 1][1]->AC(cAnimation)->AddAnimation("Kim_Idle", "Kim_Idle", 0.07f);
		m_Characters[Side == -1 ? 0 : 1][1]->GC(cAnimation)->AddAnimation("Kim_Ready", "Kim_Ready", 0.07f, false);
		m_Characters[Side == -1 ? 0 : 1][1]->GC(cAnimation)->SetAnimation("Kim_Idle");

		m_Characters[Side == -1 ? 0 : 1][2]->AC(cAnimation)->AddAnimation("Iori_Player_Idle", "Iori_Player_Idle", 0.1f);
		m_Characters[Side == -1 ? 0 : 1][2]->GC(cAnimation)->AddAnimation("Iori_Player_Ready", "Iori_Player_Ready", 0.12f, false);
		m_Characters[Side == -1 ? 0 : 1][2]->GC(cAnimation)->SetAnimation("Iori_Player_Idle");

		m_Selected[Side == -1 ? 0 : 1] = 0;
		m_IsSelected[Side == -1 ? 0 : 1] = false;
	}
}

void cSelectScene::Update()
{
	for (int Side = 0; Side < 2; Side++)
	{
		if (m_IsSelected[Side] == false)
		{
			if (INPUT->KeyDown(INPUT->m_Keys[Side][Key_Left]))
			{
				m_Selected[Side]--;
				if (m_Selected[Side] == -1)
					m_Selected[Side] += m_CharacterAmount;
			}
			if (INPUT->KeyDown(INPUT->m_Keys[Side][Key_Right]))
			{
				m_Selected[Side]++;
				if (m_Selected[Side] == m_CharacterAmount)
					m_Selected[Side] -= m_CharacterAmount;
			}

			for (int i = 0; i < m_CharacterAmount; i++)
			{
				m_Characters[Side][i]->m_Pos.x = 10000;
				m_Characters[Side][i]->m_Depth = 0.11f;
				m_Characters[Side][i]->GC(cRenderer)->m_Color = 0x90ffffff;
			}

			float Center = Side == 0 ? 960 - 600 : 960 + 600;
			m_Characters[Side][m_Selected[Side]]->m_Scale = Vec2(Sign(m_Characters[Side][m_Selected[Side]]->m_Scale.x) * 5, 5);
			m_Characters[Side][m_Selected[Side]]->m_Pos.x = Center;
			m_Characters[Side][m_Selected[Side]]->m_Depth = 0.1f;
			m_Characters[Side][m_Selected[Side]]->GC(cRenderer)->m_Color = 0xffffffff;

			int Index = m_Selected[Side];
			Index++;
			if (Index == m_CharacterAmount)
				Index -= m_CharacterAmount;
			m_Characters[Side][Index]->m_Scale = Vec2(Sign(m_Characters[Side][Index]->m_Scale.x) * 3, 3);
			m_Characters[Side][Index]->m_Pos.x = Center + 150;

			Index = m_Selected[Side];
			Index--;
			if (Index == -1)
				Index += m_CharacterAmount;
			m_Characters[Side][Index]->m_Scale = Vec2(Sign(m_Characters[Side][Index]->m_Scale.x) * 3, 3);
			m_Characters[Side][Index]->m_Pos.x = Center - 150;
		}
		else if (Side == 0)
		{
			if (INPUT->KeyDown(INPUT->m_Keys[Side][Key_Up]))
			{
				m_ModeSelected--;
				if (m_ModeSelected == -1)
					m_ModeSelected = 2;
			}
			if (INPUT->KeyDown(INPUT->m_Keys[Side][Key_Down]))
			{
				m_ModeSelected++;
				if (m_ModeSelected == 3)
					m_ModeSelected = 0;
			}
		}


		if (INPUT->KeyDown(INPUT->m_Keys[Side][Key_WPunch]))
		{
			string Key = m_Characters[Side][m_Selected[Side]]->GC(cAnimation)->m_CurAnim->Key;
			if (!m_IsSelected[Side])
			{
				m_IsSelected[Side] = true;
				m_Characters[Side][m_Selected[Side]]->GC(cAnimation)->SetAnimation(string(Key.c_str(), Key.size() - 4) + "Ready");
				SOUND->Play(string(Key.c_str(), Key.size() - 4) + "Ready", -500);
			}
			else if (Side == 0)
			{
				SYSTEM->m_GameMode = (GameMode)m_ModeSelected;

				SCENE->ChangeScene("STAGE1");
				if (m_IsSelected[0])
				{
					static_cast<cStage1Scene*>(SCENE->m_New)->m_Characters[0] = (Character)m_Selected[0];
					SYSTEM->m_PlayerRemain++;
				}
				else
					static_cast<cStage1Scene*>(SCENE->m_New)->m_Characters[0] = Char_End;

				if (m_IsSelected[1])
				{
					static_cast<cStage1Scene*>(SCENE->m_New)->m_Characters[1] = (Character)m_Selected[1];
					SYSTEM->m_PlayerRemain++;
				}
				else
					static_cast<cStage1Scene*>(SCENE->m_New)->m_Characters[1] = Char_End;
			}
		}
		if (INPUT->KeyDown(INPUT->m_Keys[Side][Key_WKick]))
		{
			string Key = m_Characters[Side][m_Selected[Side]]->GC(cAnimation)->m_CurAnim->Key;
			if (m_IsSelected[Side])
			{
				m_IsSelected[Side] = false;
				m_Characters[Side][m_Selected[Side]]->GC(cAnimation)->SetAnimation(string(Key.c_str(), Key.size() - 5) + "Idle");
			}
		}
	}
}

void cSelectScene::Render()
{
	IMAGE->Render(IMAGE->Find("Point"), Vec2(0, 0), Vec2(10000, 10000), 0, 0.9, 0xff000000);

	int Side = 0;
	float DescSize = 0.35f;
	float DescPadding = 25;
	for (int i = -1; i <= 1; i += 2)
	{
		switch (m_Selected[Side])
		{
		case Char_Kyo:
		{
			IMAGE->CenterRenderText(L"KYO KUSANAGI", Vec2(960 + 600 * i, 950), Vec2(1, 1), 0, 0.09);
			IMAGE->RenderText(L"114식 황물기: ↓ → 주먹", Vec2(20 + Side * 1200, DescPadding * 1), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L" ㄴ128식 구상: 114식 황물기 도중 → ↓ ← 주먹", Vec2(20 + Side * 1200, DescPadding * 2), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L"   ㄴ402식 벌읊기: 128식 구상 도중 ↓ → 주먹", Vec2(20 + Side * 1200, DescPadding * 3), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L"     ㄴ리 108식 대사치: 402식 벌읊기 이후 주먹 유지(차지 가능)", Vec2(20 + Side * 1200, DescPadding * 4), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L"외식 나락 떨구기: 공중에서 ↓ ↓ 주먹", Vec2(20 + Side * 1200, DescPadding * 5), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L"75식 개: ↓ → 발", Vec2(20 + Side * 1200, DescPadding * 6), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L" ㄴR.E.D. KicK: 75식 개 이후 주먹 유지(차지 가능)", Vec2(20 + Side * 1200, DescPadding * 7), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L"100식 귀신태우기: → ↓ → 주먹", Vec2(20 + Side * 1200, DescPadding * 8), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L"최종결전오의 무식: ↓ → ↓ → 주먹(게이지 소모)", Vec2(20 + Side * 1200, DescPadding * 9), Vec2(DescSize, DescSize), 0, 0.09);
			break;
		}
		case Char_Kim:
		{
			IMAGE->CenterRenderText(L"KAPHWAN KIM", Vec2(960 + 600 * i, 950), Vec2(1, 1), 0, 0.09);
			IMAGE->RenderText(L"삼연격: ↓ → 주먹(3회 반복)", Vec2(20 + Side * 1200, DescPadding * 1), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L"반월참: ← ↓ → 발(공중 가능)", Vec2(20 + Side * 1200, DescPadding * 2), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L"비연참: → ↓ → 발", Vec2(20 + Side * 1200, DescPadding * 3), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L"비상각: 공중에서 ↓ → 발", Vec2(20 + Side * 1200, DescPadding * 4), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L"봉황각: ↓ ← ↓ → 주먹(게이지 소모)", Vec2(20 + Side * 1200, DescPadding * 5), Vec2(DescSize, DescSize), 0, 0.09);
			break;
		}
		case Char_Iori:
		{
			IMAGE->CenterRenderText(L"IORI YAGAMI", Vec2(960 + 600 * i, 950), Vec2(1, 1), 0, 0.09);
			IMAGE->RenderText(L"108식 어둠쫓기: ← ↓ → 주먹", Vec2(20 + Side * 1200, DescPadding * 1), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L"100식 귀신태우기: → ↓ → 주먹", Vec2(20 + Side * 1200, DescPadding * 2), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L"127식 규화: ↓ ← 주먹(3회 반복)", Vec2(20 + Side * 1200, DescPadding * 3), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L"212식 금월 음: → ↓ ← 발", Vec2(20 + Side * 1200, DescPadding * 4), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L"311식 조즐: → ↓ → 발", Vec2(20 + Side * 1200, DescPadding * 5), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L"금 1211식 팔치녀: ↓ → ↓ ← 주먹(게이지 소모)", Vec2(20 + Side * 1200, DescPadding * 6), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L"리 316식 시화: 팔치녀 종료 직전에 ↓ → ↓ → ↓ → ↓ → 주먹(게이지 소모)", Vec2(20 + Side * 1200, DescPadding * 7), Vec2(DescSize, DescSize), 0, 0.09);
			IMAGE->RenderText(L"설풍: 가드캔슬, 무적시간이 없는 대신 적을 공중으로 띄우지 않음", Vec2(20 + Side * 1200, DescPadding * 8), Vec2(DescSize, DescSize), 0, 0.09);
			break;
		}
		}

		Side++;
	}
	if (m_IsSelected[0] == true)
	{
		IMAGE->CenterRenderText(L"PvE모드", Vec2(960, 480), m_ModeSelected == 0 ? Vec2(0.75, 0.75) : Vec2(0.5, 0.5), 0, 0.09);
		IMAGE->CenterRenderText(L"PvP모드", Vec2(960, 540), m_ModeSelected == 1 ? Vec2(0.75, 0.75) : Vec2(0.5, 0.5), 0, 0.09);
		IMAGE->CenterRenderText(L"PvP + PvE모드", Vec2(960, 600), m_ModeSelected == 2 ? Vec2(0.75, 0.75) : Vec2(0.5, 0.5), 0, 0.09);
	}
}

void cSelectScene::Release()
{
	m_Characters[0].clear();
	m_Characters[1].clear();
}
