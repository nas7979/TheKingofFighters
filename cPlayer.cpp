#include "DXUT.h"
#include "cPlayer.h"
#include "cEnemy.h"


cPlayer::cPlayer()
{
}


cPlayer::~cPlayer()
{
}

void cPlayer::Init()
{
	cCharacter::Init();
	m_Gauge = 0;
	m_GaugeStock = 0;

	GC(cRenderer)->m_PreRender = [&]()->void {
		IMAGE->m_OutlineShader->SetVector((D3DXHANDLE)"Color", &(m_Side == 0 ? D3DXVECTOR4(0, 0, 1, 1) : D3DXVECTOR4(1, 0, 0, 1)));
		IMAGE->End();
		IMAGE->Begin();
		UINT num = 0;
		IMAGE->m_OutlineShader->Begin(&num, 0);
		IMAGE->m_OutlineShader->BeginPass(0);
	};

	GC(cRenderer)->m_PostRender = [&]()->void {
		IMAGE->m_OutlineShader->EndPass();
		IMAGE->End();
		IMAGE->m_OutlineShader->End();
		IMAGE->Begin();
	};
}

void cPlayer::Update()
{
	cCharacter::Update();
	for (int i = 0; i < Key_End; i++)
	{
		if (INPUT->KeyDown(INPUT->m_Keys[m_Side][i]))
		{
			INPUT->AddToInputBuffer(m_Side, (Keys)i);
		}
	}
}

void cPlayer::Render()
{
	float Scale = 5;
	TCHAR Text[32];
	if (m_Side == 0)
	{
		IMAGE->Render(IMAGE->Find("HpBar1_Under"), Vec2(10, 10), Vec2(Scale, Scale), 0, 0.1, 0xffffffff, true);
		IMAGE->Render(IMAGE->Find("HpBar_Hp"), Vec2(10 + 31 * Scale, 10), Vec2(Clamp(m_Hp / m_MaxHp, 0, 1) * Scale * 104, Scale), 0, 0.1, 0xffffffff, true);
		wsprintf(Text, L"KILLED: %d", m_Killed);
		IMAGE->RenderText(Text, Vec2(20, 250), Vec2(1, 1), 0, 0.09, 0xffffffff, true);
		wsprintf(Text, L"DEALT: %d", m_Dealt);
		IMAGE->RenderText(Text, Vec2(20, 180), Vec2(1, 1), 0, 0.09, 0xffffffff, true);

		IMAGE->Render(IMAGE->Find("HpBar_Port_" + m_Owner->m_Name), Vec2(10, 10), Vec2(Scale, Scale), 0, 0.1, 0xffffffff, true);

		IMAGE->Render(IMAGE->Find("GaugeBar" + to_string((int)(timeGetTime() * 0.01f) % 5 + 1)), Vec2(20, 1000), Vec2(Scale, Scale), 0, 0.1, 0xffffffff, true);
		IMAGE->Render(IMAGE->Find("GaugeBar_Gauge"), Vec2(20 + 10 * Scale, 1000), Vec2(Clamp(m_Gauge / 1250, 0, 1) * Scale * 65, Scale), 0, 0.1, 0xffffffff, true);
		for (int i = 0; i < m_GaugeStock; i++)
		{
			IMAGE->Render(IMAGE->Find("GaugeBar_Stock" + to_string((int)(timeGetTime() * 0.01f) % 5 + 1)), Vec2(20 + 8 * i * Scale, 1000), Vec2(Scale, Scale), 0, 0.1, 0xffffffff, true);
		}
	}
	else
	{
		IMAGE->Render(IMAGE->Find("HpBar2_Under"), Vec2(1910, 10), Vec2(-Scale, Scale), 0, 0.1, 0xffffffff, true);
		IMAGE->Render(IMAGE->Find("HpBar_Hp"), Vec2(1910 + 31 * -Scale, 10), Vec2(Clamp(m_Hp / m_MaxHp, 0, 1) * -Scale * 104, Scale), 0, 0.1, 0xffffffff, true);
		wsprintf(Text, L"KILLED: %d", m_Killed);
		IMAGE->RenderText(Text, Vec2(1920 - 400, 250), Vec2(1, 1), 0, 0.09, 0xffffffff, true);
		wsprintf(Text, L"DEALT: %d", m_Dealt);
		IMAGE->RenderText(Text, Vec2(1920 - 400, 180), Vec2(1, 1), 0, 0.09, 0xffffffff, true);

		IMAGE->Render(IMAGE->Find("HpBar_Port_" + m_Owner->m_Name), Vec2(1910, 10), Vec2(-Scale, Scale), 0, 0.1, 0xffffffff, true);

		IMAGE->Render(IMAGE->Find("GaugeBar" + to_string((int)(timeGetTime() * 0.01f) % 5 + 1)), Vec2(1900, 1000), Vec2(-Scale, Scale), 0, 0.1, 0xffffffff, true);
		IMAGE->Render(IMAGE->Find("GaugeBar_Gauge"), Vec2(1900 - 10 * Scale, 1000), Vec2(Clamp(m_Gauge / 1250, 0, 1) * -Scale * 65, Scale), 0, 0.1, 0xffffffff, true);
		for (int i = 0; i < m_GaugeStock; i++)
		{
			IMAGE->Render(IMAGE->Find("GaugeBar_Stock" + to_string((int)(timeGetTime() * 0.01f) % 5 + 1)), Vec2(1900 - 8 * i * Scale, 1000), Vec2(-Scale, Scale), 0, 0.1, 0xffffffff, true);
		}
	}
}

void cPlayer::Release()
{
}

void cPlayer::OnCollision(cObject * _Other, RECT _Rect)
{
	cCharacter::OnCollision(_Other, _Rect);
}

void cPlayer::OnAnimationEnd(string _Key)
{
	cCharacter::OnAnimationEnd(_Key);
}

void cPlayer::OnAnimationNotify(string _Key)
{
}

void cPlayer::OnHit(string _Key, cObject * _Other, RECT _Rect)
{
	cCharacter::OnHit(_Key, _Other, _Rect);
	if (_Other->m_Tag == Obj_Enemy)
	{
		_Other->GC(cEnemy)->SetTarget(m_Owner);
	}
}

void cPlayer::Death()
{
	cCharacter::Death();
	SYSTEM->m_PlayerRemain--;
	if (SYSTEM->m_PlayerRemain == 0)
	{
		SOUND->StopAll();
		m_Voice->SetVolume(0);
		SYSTEM->HitStop(100);
		for (int i = 0; i < 9; i += 2)
		{
			SCHEDULE->AddSchedule(i * 0.015, true, []()->bool {
				cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Point"), Vec2(0, 0), Vec2(10000, 10000), 0, 0, 0.8, 0xffff0000);
				Part->SetAlpha(255, -255 * 20 * 10, 1);
				return true;
			});
			SCHEDULE->AddSchedule(i * 0.015 + 0.015, true, []()->bool {
				cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Point"), Vec2(0, 0), Vec2(10000, 10000), 0, 0, 0.8);
				Part->SetAlpha(255, -255 * 20 * 10, 1);
				return true;
			});
		}
		SCHEDULE->AddSchedule(0.3, true, [&]()->bool {
			m_Owner->m_Depth = 0.01;
			cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Point"), Vec2(0, 0), Vec2(10000, 10000), 0, 0, 0.05, 0x00000000);
			Part->SetAlpha(0, 255 * 10, 1);
			Part = PART->AddParticle<cParticle>(IMAGE->Find("GameOver"), CAMERA->m_Pos, Vec2(3, 3), 0, 0, 0.03, 0x00ffffff);
			Part->SetAlpha(0, 255 * 10, 1);
			SCHEDULE->AddSchedule(0.4, true, []()->bool {
				cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Point"), CAMERA->m_Pos + Vec2(0, -270), Vec2(10000, 0), 0, 0, 0.01, 0xff000000);
				Part->SetScale(Vec2(0, 2500), 1);
				Part = PART->AddParticle<cParticle>(IMAGE->Find("Point"), CAMERA->m_Pos + Vec2(0, 270), Vec2(10000, 0), 0, 0, 0.01, 0xff000000);
				Part->SetScale(Vec2(0, 2500), 1);

				SCHEDULE->AddSchedule(0.25, true, []()->bool {
					SCENE->ChangeScene("RESULT");
					return true;
				});
				return true;
			});
			return true;
		});
	}
	else
	{
		for (auto& iter : OBJECT->m_Objects[Obj_Enemy])
		{
			iter->GC(cEnemy)->m_Target = SYSTEM->m_Player[!m_Side]->GC(cCharacter);
		}
	}
}

void cPlayer::AddHitBox(Vec2 _Size, Vec2 _Pos, float _Time, float _Damage, float _Stun, Vec2 _Force, float _Z, float _HitTime, float _StopTime, float _Shake, string _Event, bool _DodgeAble, int _EffectSize)
{
	cObject* a = OBJECT->AddObject("HitBox", m_Owner->m_Pos, m_Owner->m_Z, 0, Obj_HitBox);
	m_HitBox = a->AC(cHitBox);
	a->GC(cCollider)->m_Size = _Size;
	a->GC(cCollider)->m_Offset = _Pos;
	a->SetAlarm(0, _Time);
	m_HitBox->m_Damage = _Damage;
	m_HitBox->m_Stun = _Stun;
	m_HitBox->m_Force = _Force;
	m_HitBox->m_Z = _Z;
	m_HitBox->m_HitTime = _HitTime;
	m_HitBox->m_StopTime = _StopTime;
	m_HitBox->m_Shake = _Shake;
	m_HitBox->m_Event = _Event;
	m_HitBox->m_DodgeAble = _DodgeAble;
	m_HitBox->m_Character = this;
	m_HitBox->m_Size = _EffectSize;
	a->GC(cCollider)->m_CollWith.push_back(Obj_Enemy);
	if(SYSTEM->m_GameMode == GM_PvP || SYSTEM->m_GameMode == GM_PvPvE)
		a->GC(cCollider)->m_CollWith.push_back(Obj_Player);
}

void cPlayer::SetSide(int _Side)
{
	m_Side = _Side;
	SYSTEM->m_Player[_Side] = m_Owner;
}

void cPlayer::AddGauge(int _Gauge)
{
	if (m_GaugeStock == 3)
		return;
	if (SYSTEM->m_GameMode == GM_PvP)
		_Gauge *= 2;
	m_Gauge += _Gauge;
	if (m_Gauge >= 1250)
	{
		m_Gauge -= 1250;
		m_GaugeStock++;
		if (m_GaugeStock == 3)
			m_Gauge = 0;
	}
}
