#include "DXUT.h"
#include "cDuck.h"


cDuck::cDuck()
{
}


cDuck::~cDuck()
{
}

void cDuck::Init()
{
	cEnemy::Init();
	GC(cCollider)->Setting(Vec2(30, 50), Vec2(0, 0));
	GC(cRenderer)->m_ShadowOffset = -25;

	GC(cAnimation)->AddAnimation("Idle", m_Owner->m_Name + "_Idle", 0.09);
	GC(cAnimation)->AddAnimation("Walk", m_Owner->m_Name + "_Walk", 0.1);
	GC(cAnimation)->AddAnimation("Wake", m_Owner->m_Name + "_Wake", 0.07);

	GC(cAnimation)->AddAnimation("Attack1", m_Owner->m_Name + "_Attack1_", 0.09);
	GC(cAnimation)->AddNotify("Attack1", 4, "Attack1_Force1");
	GC(cAnimation)->AddNotify("Attack1", 5, "Attack1_Attack1");
	GC(cAnimation)->AddNotify("Attack1", 10, "Attack1_Attack2");

	GC(cAnimation)->AddAnimation("Attack2", m_Owner->m_Name + "_Attack2_", 0.08);
	GC(cAnimation)->AddNotify("Attack2", 9, "Attack2_Attack1");

	GC(cAnimation)->SetAnimation("Idle");


	m_MaxHp = 175;
	m_Hp = m_MaxHp;

	m_MaxStun = 125;
	m_Stun = m_MaxStun;

	m_HitSound = 4;
	m_Speed = 200;
}

void cDuck::Update()
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
						PlayVoice(RandomText("Duck_Attack", 1, 4));
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
						PlayVoice(RandomText("Duck_Attack", 1, 4));
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

void cDuck::Render()
{
	cEnemy::Render();
}

void cDuck::Release()
{
	cEnemy::Release();
}

void cDuck::OnCollision(cObject * _Other, RECT _Rect)
{
	cEnemy::OnCollision(_Other, _Rect);
}

void cDuck::OnAnimationEnd(string _Key)
{
	cEnemy::OnAnimationEnd(_Key);
}

void cDuck::OnAnimationNotify(string _Key)
{
	if (_Key == "Attack2_Attack1")
	{
		AddForce(75, 0);
		AddHitBox(Vec2(25, 25), Vec2(30, -30), 0.1, 75, 0, Vec2(300, 0), 30, 0.75, 0.3, 6);
		return;
	}

	if (_Key == "Attack1_Force1")
	{
		AddForce(500, 0);
		return;
	}
	if (_Key == "Attack1_Attack1")
	{
		AddHitBox(Vec2(30, 20), Vec2(30, -5), 0.1, 40, 0, Vec2(250, 0), 25, 0.6, 0.2, 5);
		return;
	}
	if (_Key == "Attack1_Attack2")
	{
		AddHitBox(Vec2(30, 20), Vec2(35, -5), 0.1, 40, 0, Vec2(300, 0), 25, 1, 0.2, 5);
		AddForce(300, 0);
		PlayVoice(RandomText("Duck_Attack", 1, 4));
		return;
	}
}

void cDuck::OnHit(string _Key, cObject * _Other, RECT _Rect)
{
	cEnemy::OnHit(_Key, _Other, _Rect);
}
