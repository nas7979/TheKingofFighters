#include "DXUT.h"
#include "cResultScene.h"


cResultScene::cResultScene()
{
}


cResultScene::~cResultScene()
{
}

void cResultScene::Init()
{
	m_InTyping = true;
	m_Name.clear();
	SOUND->Play("BGM_Clear", 0);
	CAMERA->m_Pos = Vec2(960, 540);
	CAMERA->SetScale(1);
}

void cResultScene::Update()
{
	if (m_InTyping)
	{
		if (m_Name.size() != 3)
		{
			for (int i = 'A'; i <= 'Z'; i++)
			{
				if (INPUT->KeyDown(i))
				{
					m_Name.push_back(i);
					break;
				}
			}
		}
		if (m_Name.size() != 0)
		{
			if (INPUT->KeyDown(VK_BACK))
			{
				m_Name.pop_back();
			}
		}

		if (m_Name.size() == 3)
		{
			if (INPUT->KeyDown(VK_RETURN))
			{
				m_InTyping = false;
				SYSTEM->m_Ranking.push_back(Rank{ m_Name, SYSTEM->m_Score });
				SYSTEM->SortRank();
				SOUND->Play("Gauge", -500);
			}
		}
	}
	else
	{
		if (INPUT->KeyDown(VK_RETURN))
		{
			cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Point"), Vec2(0, 0), Vec2(10000, 10000), 0, 0, 0, 0x00000000);
			Part->SetAlpha(0, 255, 1);
			SCHEDULE->AddSchedule(1, true, []()->bool {
				SCENE->ChangeScene("TITLE");
				return true;
			});
		}
	}
}

void cResultScene::Render()
{
	TCHAR Text[64];
	IMAGE->CenterRender(IMAGE->Find(SYSTEM->m_Win ? "Clear2" : "GameOver"), Vec2(960, 100), Vec2(3, 3), 0, 0.1);

	wsprintf(Text, L"SCORE: %d", SYSTEM->m_Score);
	IMAGE->CenterRenderText(Text, Vec2(960, 300), Vec2(2, 2), 0, 0.1);

	for (int i = 0; i < 3; i++)
	{
		IMAGE->CenterRenderText(L"_", Vec2(880 + i * 80, 450), Vec2(2, 2), 0, 0.1);
	}
	for (int i = 0; i < m_Name.size(); i++)
	{
		IMAGE->CenterRenderText(wstring(1, m_Name[i]), Vec2(880 + i * 80, 450), Vec2(2, 2), 0, 0.1);
	}

	int i = 0;
	for (auto& iter : SYSTEM->m_Ranking)
	{
		IMAGE->RenderText(to_wstring(i + 1) + L". " + iter.Name, Vec2(600, 550 + i * 70), Vec2(1, 1), 0, 0.1);
		IMAGE->RenderText(to_wstring(iter.Score), Vec2(1000, 550 + i * 70), Vec2(1, 1), 0, 0.1);
		i++;
		if (i == 5)
			break;
	}
}

void cResultScene::Release()
{
}
