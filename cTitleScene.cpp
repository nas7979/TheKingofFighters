#include "DXUT.h"
#include "cTitleScene.h"


cTitleScene::cTitleScene()
{
}


cTitleScene::~cTitleScene()
{
}

void cTitleScene::Init()
{
	CAMERA->m_Pos = Vec2(960, 540);
	CAMERA->SetScale(1);
	SYSTEM->PlayerInit();
	SOUND->Play("BGM_Title", 0, true);
	cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Point"), Vec2(0, 0), Vec2(10000, 1500), 0, 0, 0, 0xff000000);
	Part->SetScale(Vec2(0, -1000), 1.02);
	Part = PART->AddParticle<cParticle>(IMAGE->Find("Point"), Vec2(0, 1080), Vec2(10000, 1500), 0, 0, 0, 0xff000000);
	Part->SetScale(Vec2(0, -1000), 1.02);

	m_Scale[0] = Vec2(1, 1);
	m_Scale[1] = Vec2(1, 1);
	m_Scale[2] = Vec2(1, 1);
	m_Scale[3] = Vec2(1, 1);
	m_Color[0] = 0xffffffff;
	m_Color[1] = 0xffffffff;
	m_Color[2] = 0xffffffff;
	m_Color[3] = 0xffffffff;
	m_Text[0] = L"START";
	m_Text[1] = L"HOW TO PLAY";
	m_Text[2] = L"RANKING";
	m_Text[3] = L"QUIT";
	m_Selected = 0;
	m_InTitle = true;
}

void cTitleScene::Update()
{
	if (m_InTitle)
	{
		if (INPUT->KeyDown('W'))
		{
			m_Selected--;
			if (m_Selected == -1)
				m_Selected = 3;
		}
		if (INPUT->KeyDown('S'))
		{
			m_Selected++;
			if (m_Selected == 4)
				m_Selected = 0;
		}
	}

	if (INPUT->KeyDown('H'))
	{
		switch (m_Selected)
		{
		case 0:
		{
			cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Point"), Vec2(0, 0), Vec2(10000, 0), 0, 0, 0, 0xff000000);
			Part->SetScale(Vec2(0, 1500), 0.99);
			Part = PART->AddParticle<cParticle>(IMAGE->Find("Point"), Vec2(0, 1080), Vec2(10000, 0), 0, 0, 0, 0xff000000);
			Part->SetScale(Vec2(0, 1500), 0.99);
			SCHEDULE->AddSchedule(1, true, []()->bool {
				SCENE->ChangeScene("SELECT");
				return true;
			});
		}
			break;

		case 1:
		case 2:
			m_InTitle = !m_InTitle;
			break;

		case 3:
			exit(0);
			break;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (m_Selected == i)
		{
			m_Color[i] = 0xffffffff;
			m_Scale[i] = Lerp<Vec2>(m_Scale[i], Vec2(1.5, 1.5), 0.1);
		}
		else
		{
			m_Color[i] = 0x90ffffff;
			m_Scale[i] = Lerp<Vec2>(m_Scale[i], Vec2(1, 1), 0.1);
		}
	}
}

void cTitleScene::Render()
{
	for (int i = 0; i < 4; i++)
	{
		IMAGE->CenterRenderText(m_Text[i], Vec2(1550 - 25 * i, 500 + 150 * i), m_Scale[i], 0, 0.1, m_Color[i]);
	}
	IMAGE->CenterRender(IMAGE->Find("Title"), Vec2(960, 540), Vec2(4, 4), 0, 0.9);
	if (m_InTitle == false)
	{
		IMAGE->CenterRender(IMAGE->Find("Window"), Vec2(960, 540), Vec2(8, 8), 0, 0.05);
		if (m_Selected == 1)
		{
			IMAGE->CenterRender(IMAGE->Find("How"), Vec2(960, 540), Vec2(1, 1), 0, 0.05);
		}
		else
		{
			IMAGE->CenterRenderText(L"RANKING", Vec2(960, 200), Vec2(3, 3), 0, 0.04, 0xffff0000);
			int i = 0;
			for (auto& iter : SYSTEM->m_Ranking)
			{
				IMAGE->RenderText(to_wstring(i + 1) + L". " + iter.Name, Vec2(600, 400 + i * 80), Vec2(1, 1), 0, 0.04);
				IMAGE->RenderText(to_wstring(iter.Score), Vec2(1000, 400 + i * 80), Vec2(1, 1), 0, 0.04);
				i++;
				if (i == 5)
					break;
			}
		}
	}
}

void cTitleScene::Release()
{
}
