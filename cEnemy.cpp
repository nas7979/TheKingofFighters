#include "DXUT.h"
#include "cEnemy.h"
#include "cItem.h"
#include "cStage1Scene.h"

cEnemy::cEnemy()
{
}


cEnemy::~cEnemy()
{
}

void cEnemy::Init()
{
	cCharacter::Init();
	GC(cAnimation)->AddAnimation("Guard_Start", m_Owner->m_Name + "_Guard_Start", 0.1, false);
	GC(cAnimation)->AddAnimation("Guard_Hit", m_Owner->m_Name + "_Guard_Hit", 0.1);
	GC(cAnimation)->AddAnimation("Stun", m_Owner->m_Name + "_Stun", 0.1);

	m_Range = Random(25, 100);
	m_TargetZ = Random(0, 150);
	int Target = Random(0, SYSTEM->m_PlayerRemain - 1);
	if (Target == 0 && SYSTEM->m_Player[0] == nullptr) Target = 1;
	m_Target = SYSTEM->m_Player[Target]->GC(cCharacter);
	if (m_Target->m_Dead == true)
		m_Target = SYSTEM->m_Player[!Target]->GC(cCharacter);

	m_Owner->SetAlarmSize(4);
	m_Owner->m_AlarmFunc = [&](int _Index)->void {
		switch (_Index)
		{
		case 0:
			if (m_MainState == State_Hit && m_SubState == State_Ground && m_Dead == false && m_AlwaysSuper == false)
			{
				m_MainState = State_Guard;
				GC(cAnimation)->SetAnimation("Guard_Start");
				m_Owner->SetAlarm(3, Random(0.5f, 1.f));
			}
			if (m_AlwaysSuper == true && m_MainState == State_Hit && m_SubState == State_Ground)
			{
				Idle();
			}
			GC(cRenderer)->SetFire(false);
			break;

		case 1:
			if (m_MainState == State_Down && m_Dead == false)
			{
				GC(cAnimation)->SetAnimation("Wake");
			}
			break;

		case 2:
			if (m_MainState == State_Stun)
			{
				Idle();
				m_Stun = m_MaxStun;
			}
			break;

		case 3:
			if (m_MainState == State_Guard)
			{
				Idle();
			}
			break;
		}
	};
}

void cEnemy::Update()
{
	cCharacter::Update();
	if (m_MainState != State_Walk && m_MainState != State_Idle && m_MainState != State_Down)
	{
		m_Owner->m_Pos.x = Clamp(m_Owner->m_Pos.x, 500, 2500);
	}
}

void cEnemy::Render()
{
	if (m_Hp > 0)
	{
		IMAGE->Render(IMAGE->Find("EnemyHpBar_Under"), Vec2(m_Owner->m_Pos.x - 40, m_Owner->m_Pos.y - 75 - m_Owner->m_Z), Vec2(1, 1), 0, m_Owner->m_Depth - 0.01);
		IMAGE->Render(IMAGE->Find("EnemyHpBar_Hp"), Vec2(m_Owner->m_Pos.x - 39, m_Owner->m_Pos.y - 75 - m_Owner->m_Z), Vec2(Clamp(m_Hp / m_MaxHp, 0, 1) * 78, 1), 0, m_Owner->m_Depth - 0.01);
		IMAGE->Render(IMAGE->Find("EnemyHpBar_Stun"), Vec2(m_Owner->m_Pos.x - 37, m_Owner->m_Pos.y - 75 - m_Owner->m_Z), Vec2(Clamp(m_Stun / m_MaxStun, 0, 1) * 74, 1), 0, m_Owner->m_Depth - 0.01);
		IMAGE->Render(IMAGE->Find("EnemyHpBar_Upper"), Vec2(m_Owner->m_Pos.x - 40, m_Owner->m_Pos.y - 75 - m_Owner->m_Z), Vec2(1, 1), 0, m_Owner->m_Depth - 0.01);
	}
}

void cEnemy::Release()
{
	cCharacter::Release();
}

void cEnemy::OnCollision(cObject * _Other, RECT _Rect)
{
	cCharacter::OnCollision(_Other, _Rect);
}

void cEnemy::OnAnimationEnd(string _Key)
{
	cCharacter::OnAnimationEnd(_Key);
	if (_Key == "Attack1" || _Key == "Attack2" || _Key == "Attack3")
	{
		Idle();
		return;
	}

	if (_Key == "Guard_Hit")
	{
		GC(cAnimation)->SetAnimation("Guard_Start");
		GC(cAnimation)->m_Frame = 2;
		return;
	}
}

void cEnemy::OnAnimationNotify(string _Key)
{
}

void cEnemy::OnHit(string _Key, cObject * _Other, RECT _Rect)
{
	cCharacter::OnHit(_Key, _Other, _Rect);
	SetTarget(_Other);
}

void cEnemy::Death()
{
	cCharacter::Death();
	if (m_Owner->m_Name != "Iori" && m_Owner->m_Name != "Rugal")
	{
		int Rand = Random(0, 7);
		if (Rand == 0)
			OBJECT->AddObject("Item_Hp", Vec2(m_Owner->m_Pos.x, -20), m_Owner->m_Z, m_Owner->m_Depth, Obj_Item)->AC(cItem);
	}
	else
	{
		static_cast<cStage1Scene*>(SCENE->m_Cur)->AddEnemy();
		m_Voice->SetVolume(0);
		SYSTEM->HitStop(3);
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
	}

	SCHEDULE->AddSchedule(3, true, [&]()->bool {
		float Time = 3;
		while (Time > 0)
		{
			Time -= 0.1;
			cRenderer* Renderer = GetComponent<cRenderer>();
			SCHEDULE->AddSchedule(Time, true, [=]()->bool {
				Renderer->m_Color = (Renderer->m_Color & 0x00ffffff) | ((Renderer->m_Color & 0xff000000) == 0xff000000 ? 0x00000000 : 0xff000000);
				return true;
			});
		}
		SCHEDULE->AddSchedule(3, true, [&]()->bool {
			m_Owner->m_Destroyed = true;
			return true;
		});
		return true;
	});
}

void cEnemy::SetTarget(cObject * _Target)
{
	if (Random(0, 9) <= 2)
	{
		m_Target = _Target->GC(cCharacter);
	}
}
