#include "DXUT.h"
#include "cBig.h"


cBig::cBig()
{
}


cBig::~cBig()
{
}

void cBig::Init()
{
	cEnemy::Init();
	GC(cCollider)->Setting(Vec2(30, 55), Vec2(0, 0));
	GC(cRenderer)->m_ShadowOffset = -25;

	GC(cAnimation)->AddAnimation("Idle", m_Owner->m_Name + "_Idle", 0.1);
	GC(cAnimation)->AddAnimation("Walk", m_Owner->m_Name + "_Walk", 0.11);
	GC(cAnimation)->AddAnimation("Wake", m_Owner->m_Name + "_Wake", 0.1);

	GC(cAnimation)->AddAnimation("Attack1", m_Owner->m_Name + "_Attack1_", 0.09);
	GC(cAnimation)->AddNotify("Attack1", 9, "Attack1_Attack1");

	GC(cAnimation)->AddAnimation("Attack2", m_Owner->m_Name + "_Attack2_", 0.08);
	GC(cAnimation)->AddNotify("Attack2", 2, "Attack2_Force1");
	GC(cAnimation)->AddNotify("Attack2", 9, "Attack2_Attack1");
	GC(cAnimation)->AddNotify("Attack2", 13, "Attack2_Attack2");
	GC(cAnimation)->AddNotify("Attack2", 17, "Attack2_Attack3");

	GC(cAnimation)->SetAnimation("Idle");


	m_MaxHp = 300;
	m_Hp = m_MaxHp;

	m_MaxStun = 175;
	m_Stun = m_MaxStun;

	m_HitSound = 3;
	m_Speed = 150;
}

void cBig::Update()
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
						GC(cAnimation)->SetAnimation("Attack1");
						PlayVoice(RandomText("Big_Attack", 1, 5));
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
						GC(cAnimation)->SetAnimation("Attack2");
						PlayVoice(RandomText("Big_Attack", 1, 5));
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

void cBig::Render()
{
	cEnemy::Render();
}

void cBig::Release()
{
	cEnemy::Release();
}

void cBig::OnCollision(cObject * _Other, RECT _Rect)
{
	cEnemy::OnCollision(_Other, _Rect);
}

void cBig::OnAnimationEnd(string _Key)
{
	cEnemy::OnAnimationEnd(_Key);
}

void cBig::OnAnimationNotify(string _Key)
{
	if (_Key == "Attack1_Attack1")
	{
		AddHitBox(Vec2(50, 10), Vec2(50, -15), 0.2, 75, 0, Vec2(300, 0), 15, 0.75, 0.25, 5);
		return;
	}

	if (_Key == "Attack2_Force1")
	{
		AddForce(500, 0);
		return;
	}
	if (_Key == "Attack2_Attack1")
	{
		AddHitBox(Vec2(30, 40), Vec2(40, -30), 0.1, 30, 0, Vec2(250, 0), 30, 0.6, 0.2, 5);
		AddForce(300, 0);
		PlayVoice(RandomText("Big_Attack", 1, 5));
		return;
	}
	if (_Key == "Attack2_Attack2")
	{
		AddHitBox(Vec2(30, 40), Vec2(40, -30), 0.1, 30, 0, Vec2(250, 0), 30, 0.6, 0.2, 5);
		AddForce(300, 0);
		PlayVoice(RandomText("Big_Attack", 1, 5));
		return;
	}
	if (_Key == "Attack2_Attack3")
	{
		AddHitBox(Vec2(40, 40), Vec2(0, -30), 0.1, 40, 0, Vec2(100, 1000), 30, 0.6, 0.3, 7);
		AddForce(250, 0);
		PlayVoice(RandomText("Big_Attack", 1, 5));
		return;
	}
}

void cBig::OnHit(string _Key, cObject * _Other, RECT _Rect)
{
	cEnemy::OnHit(_Key, _Other, _Rect);
}
