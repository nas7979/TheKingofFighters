#include "DXUT.h"
#include "cRobert.h"


cRobert::cRobert()
{
}


cRobert::~cRobert()
{
}

void cRobert::Init()
{
	cEnemy::Init();
	GC(cCollider)->Setting(Vec2(30, 50), Vec2(0, 0));
	GC(cRenderer)->m_ShadowOffset = -25;

	GC(cAnimation)->AddAnimation("Idle", m_Owner->m_Name + "_Idle", 0.09);
	GC(cAnimation)->AddAnimation("Walk", m_Owner->m_Name + "_Walk", 0.09);
	GC(cAnimation)->AddAnimation("Wake", m_Owner->m_Name + "_Wake", 0.1);

	GC(cAnimation)->AddAnimation("Attack1", m_Owner->m_Name + "_Attack1_", 0.085);
	GC(cAnimation)->AddNotify("Attack1", 13, "Attack1_Attack1");

	GC(cAnimation)->AddAnimation("Attack2", m_Owner->m_Name + "_Attack2_", 0.075);
	GC(cAnimation)->AddNotify("Attack2", 7, "Attack2_Attack1");
	GC(cAnimation)->AddNotify("Attack2", 19, "Attack2_Attack2");

	GC(cAnimation)->SetAnimation("Idle");

	m_MaxHp = 200;
	m_Hp = m_MaxHp;

	m_MaxStun = 125;
	m_Stun = m_MaxStun;

	m_HitSound = 3;
	m_Speed = 150;
}

void cRobert::Update()
{
	cEnemy::Update();
	if (m_MainState == State_Idle || m_MainState == State_Walk)
	{
		if (m_SubState == State_Ground)
		{
			float Dist = abs(m_Owner->m_Pos.x - m_Target->m_Owner->m_Pos.x);
			if (m_Target->m_Ground != nullptr && m_Target->m_Ground != m_Ground)
			{
				m_TargetZ = m_Target->m_Owner->m_Z;
				if (Dist > 10)
				{
					Move();
				}
				else
				{
					Idle();
				}
				if (Random(0, (int)(2.f / DT)) == 0)
				{
					if (Dist <= 100 && abs(m_TargetZ - m_Owner->m_Z) < 5)
					{
						Jump();
						m_Velocity.x = Dist * m_Owner->m_Scale.x * 1.2;
					}
				}
			}
			else
			{
				if (Dist <= m_Range)
				{
					if (Random(0, (int)(2.f / DT)) == 0)
					{
						m_MainState = State_Attack;
						GC(cAnimation)->SetAnimation("Attack2");
						PlayVoice("Robert_Attack2");
					}
					else
					{
						Idle();
					}
				}
				else
				{
					if (Random(0, (int)(3.f / DT)) == 0)
					{
						m_MainState = State_Attack;
						GC(cAnimation)->SetAnimation("Attack1");
						PlayVoice("Robert_Attack1");
					}
					else
					{
						Move();
					}
				}
				if (Random(0, (int)(10.f / DT)) == 0)
				{
					m_TargetZ = Random(0, 150);
				}
			}
			m_Owner->m_Scale.x = Sign(m_Target->m_Owner->m_Pos.x - m_Owner->m_Pos.x);
		}
	}
}

void cRobert::Render()
{
	cEnemy::Render();
}

void cRobert::Release()
{
	cEnemy::Release();
}

void cRobert::OnCollision(cObject * _Other, RECT _Rect)
{
	cEnemy::OnCollision(_Other, _Rect);
}

void cRobert::OnAnimationEnd(string _Key)
{
	cEnemy::OnAnimationEnd(_Key);
}

void cRobert::OnAnimationNotify(string _Key)
{
	if (_Key == "Attack1_Attack1")
	{
		AddHitBox(Vec2(30, 15), Vec2(0,0), 100, 50, 0, Vec2(200, 0), 30, 0.75, 0.12, 4, "Hit");
		FireMissile("Robert_Attack1_Missile", 0.1, m_Owner->m_Pos, 400, m_Owner->m_Scale.x == 1 ? 0 : 180)->m_Owner->SetAlarm(0, 10);
		return;
	}

	if (_Key == "Attack2_Attack1")
	{
		AddHitBox(Vec2(20, 40), Vec2(40, 0), 0.1, 30, 0, Vec2(300, 0), 25, 0.5, 0.2, 5);
		AddForce(300, 0);
		return;
	}

	if (_Key == "Attack2_Attack2")
	{
		AddHitBox(Vec2(30, 40), Vec2(0, 0), 0.1, 50, 0, Vec2(100, 1000), 25, 1, 0.35, 6);
		AddForce(250, 0);
		return;
	}
}

void cRobert::OnHit(string _Key, cObject * _Other, RECT _Rect)
{
	cEnemy::OnHit(_Key, _Other, _Rect);
}
