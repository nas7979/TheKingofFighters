#include "DXUT.h"
#include "cRalf.h"


cRalf::cRalf()
{
}


cRalf::~cRalf()
{
}

void cRalf::Init()
{
	cEnemy::Init();
	GC(cCollider)->Setting(Vec2(30, 50), Vec2(0, 0));
	GC(cRenderer)->m_ShadowOffset = -25;

	GC(cAnimation)->AddAnimation("Idle", m_Owner->m_Name + "_Idle", 0.08);
	GC(cAnimation)->AddAnimation("Walk", m_Owner->m_Name + "_Walk", 0.1);
	GC(cAnimation)->AddAnimation("Wake", m_Owner->m_Name + "_Wake", 0.085);

	GC(cAnimation)->AddAnimation("Attack1", m_Owner->m_Name + "_Attack1_", 0.09);
	GC(cAnimation)->AddNotify("Attack1", 15, "Attack1_Attack1");

	GC(cAnimation)->AddAnimation("Attack2_Start", m_Owner->m_Name + "_Attack2_Start_", 0.07);
	GC(cAnimation)->AddAnimation("Attack2_Fire", m_Owner->m_Name + "_Attack2_Fire_", 0.1, false);
	GC(cAnimation)->AddNotify("Attack2_Fire", 2, "Attack2_Force1");
	GC(cAnimation)->AddAnimation("Attack2_End", m_Owner->m_Name + "_Attack2_End_", 0.09);

	GC(cAnimation)->AddAnimation("Attack3_Start", m_Owner->m_Name + "_Attack3_Start_", 0.35);
	GC(cAnimation)->AddAnimation("Attack3_Fire", m_Owner->m_Name + "_Attack3_Fire_", 0.05);
	GC(cAnimation)->AddNotify("Attack3_Fire", 2, "Attack3_Attack1");
	GC(cAnimation)->AddNotify("Attack3_Fire", 5, "Attack3_Attack1");
	GC(cAnimation)->AddNotify("Attack3_Fire", 8, "Attack3_Attack1");

	GC(cAnimation)->SetAnimation("Idle");


	m_MaxHp = 500;
	m_Hp = m_MaxHp;

	m_MaxStun = 250;
	m_Stun = m_MaxStun;

	m_HitSound = 3;
	m_Speed = 150;
}

void cRalf::Update()
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
					if (Dist <= 200 && abs(m_TargetZ - m_Owner->m_Z) < 5)
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
					if (Random(0, (int)(1.5f / DT)) == 0)
					{
						if (Random(0, 1) == 0)
						{
							m_MainState = State_Attack;
							GC(cAnimation)->SetAnimation("Attack1");
							m_SuperArmor = true;
						}
						else
						{
							m_MainState = State_Attack;
							GC(cAnimation)->SetAnimation("Attack3_Start");
							m_Looped = 0;
						}
					}
					else
					{
						Idle();
					}
				}
				else
				{
					if (Random(0, (int)(2.5f / DT)) == 0)
					{
						m_MainState = State_Attack;
						GC(cAnimation)->SetAnimation("Attack2_Start");
						PlayVoice("Ralf_Attack2_Start");
						cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
						Anim->m_Anim = IMAGE->FindAnimation("Flash");
						Anim->m_Speed = 0.05;
						SOUND->Play("Flash", -500);
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

void cRalf::Render()
{
	cEnemy::Render();
}

void cRalf::Release()
{
	cEnemy::Release();
}

void cRalf::OnCollision(cObject * _Other, RECT _Rect)
{
	cEnemy::OnCollision(_Other, _Rect);
}

void cRalf::OnAnimationEnd(string _Key)
{
	cEnemy::OnAnimationEnd(_Key);
	if (_Key == "Attack2_Start")
	{
		GC(cAnimation)->SetAnimation("Attack2_Fire");
		return;
	}

	if (_Key == "Attack2_Fire")
	{
		GC(cAnimation)->SetAnimation("Attack2_End");
		return;
	}

	if (_Key == "Attack2_End")
	{
		Idle();
		return;
	}

	if (_Key == "Attack3_Start")
	{
		GC(cAnimation)->SetAnimation("Attack3_Fire");
		PlayVoice("Ralf_Attack3");
		return;
	}

	if (_Key == "Attack3_Fire")
	{
		m_Looped++;
		if (m_Looped == 5)
		{
			Idle();
		}
		return;
	}
}

void cRalf::OnAnimationNotify(string _Key)
{
	if (_Key == "Attack1_Attack1")
	{
		AddHitBox(Vec2(20, 40), Vec2(30, 0), 0.1, 100, 0, Vec2(75, -800), 30, 1, 0.4, 6);
		PlayVoice("Ralf_Attack1");
		if (m_AlwaysSuper == false)
		{
			m_SuperArmor = false;
		}
		return;
	}

	if (_Key == "Attack2_Force1")
	{
		AddForce(1500, 0);
		PlayVoice("Ralf_Attack2_Fire");
		SOUND->Play("Ralf_Attack2_Effect", -500);
		AddHitBox(Vec2(30, 20), Vec2(30, 0), 0.5, 125, 0, Vec2(150, -1000), 35, 2, 0.5, 9, "Attack2", false);
		GC(cAnimation)->m_Speed = 0.2;
		return;
	}

	if (_Key == "Attack3_Attack1")
	{
		AddHitBox(Vec2(20, 30), Vec2(20, -30), 0.05, 20, 0, Vec2(20, -300), 25, 0.5, 0.04, 4, "Fire");
		SOUND->Play("Ralf_Attack3_Effect", -500);
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos + Vec2(Random(30, 60) * m_Owner->m_Scale.x, Random(-40, -70)), Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation(RandomText("Fire_Small", 1, 2, true));
		Anim->m_Speed = 0.05;
		return;
	}
}

void cRalf::OnHit(string _Key, cObject * _Other, RECT _Rect)
{
	if (_Key == "Attack2")
	{
		GC(cAnimation)->SetAnimation("Attack2_End");
		AddForce(200, 0);
		SOUND->Play("Explosion1", -500);
		_Key = "Fire";
	}
	cEnemy::OnHit(_Key, _Other, _Rect);
}
