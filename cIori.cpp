#include "DXUT.h"
#include "cIori.h"


cIori::cIori()
{
}


cIori::~cIori()
{
}

void cIori::Init()
{
	cEnemy::Init();
	GC(cCollider)->Setting(Vec2(30, 40), Vec2(0, 0));
	GC(cRenderer)->m_ShadowOffset = -25;

	GC(cAnimation)->AddAnimation("Idle", m_Owner->m_Name + "_Idle", 0.11);
	GC(cAnimation)->AddAnimation("Walk", m_Owner->m_Name + "_Walk", 0.1);
	GC(cAnimation)->AddAnimation("Wake", m_Owner->m_Name + "_Wake", 0.1);
	GC(cAnimation)->AddAnimation("Intro", m_Owner->m_Name + "_Intro", 0.1);
	GC(cAnimation)->AddNotify("Intro", 13, "Intro");

	GC(cAnimation)->AddAnimation("Aoi", m_Owner->m_Name + "_Aoi", 0.07);
	GC(cAnimation)->AddNotify("Aoi", 3, "Aoi_Force1");
	GC(cAnimation)->AddNotify("Aoi", 4, "Aoi_Attack1");
	GC(cAnimation)->AddNotify("Aoi", 8, "Aoi_Attack2");
	GC(cAnimation)->AddNotify("Aoi", 11, "Aoi_Force2");
	GC(cAnimation)->AddNotify("Aoi", 14, "Aoi_Attack3");

	GC(cAnimation)->AddAnimation("CD", m_Owner->m_Name + "_CD_Air", 0.05);
	GC(cAnimation)->AddNotify("CD", 5, "CD_Attack1");

	GC(cAnimation)->AddAnimation("Yami", m_Owner->m_Name + "_Yami", 0.09);
	GC(cAnimation)->AddNotify("Yami", 4, "Yami_Attack1");

	GC(cAnimation)->AddAnimation("Kuzu_Start", m_Owner->m_Name + "_Kuzu_Start", 0.08);
	GC(cAnimation)->AddNotify("Kuzu_Start", 10, "Kuzu_Attack1");
	GC(cAnimation)->AddAnimation("Kuzu_Hit", m_Owner->m_Name + "_Kuzu_Hit", 0.1);
	GC(cAnimation)->AddNotify("Kuzu_Hit", 8, "Kuzu_Attack2");
	GC(cAnimation)->AddAnimation("Kuzu_Miss", m_Owner->m_Name + "_Kuzu_Miss", 0.2);

	GC(cAnimation)->SetAnimation("Intro");
	OBJECT->m_Boss = m_Owner;
	m_Intro = true;
	m_Invincible = true;
	m_AlwaysSuper = true;

	m_MaxHp = 1500;
	m_Hp = m_MaxHp;

	m_MaxStun = 150;
	m_Stun = m_MaxStun;

	m_HitSound = 4;
	m_Speed = 400;
	m_MainState = State_Skill;
}

void cIori::Update()
{
	cEnemy::Update();
	if (m_Intro)
		return;
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
				if (Dist <= 75)
				{
					if (Random(0, (int)(1.f / DT)) == 0)
					{
						if (abs(m_Owner->m_Pos.y - m_Target->m_Owner->m_Pos.y) <= 15)
						{
							if (Random(0, 2) == 0)
							{
								m_MainState = State_Skill;
								GC(cAnimation)->SetAnimation("Aoi");
								GC(cAnimation)->m_Speed = 0.4;
							}
							else
							{
								m_MainState = State_Attack;
								GC(cAnimation)->SetAnimation("Kuzu_Start");
								PlayVoice("Iori_Kuzu_Start");
								cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
								Anim->m_Anim = IMAGE->FindAnimation("Flash");
								Anim->m_Speed = 0.05;
								SOUND->Play("Flash", -500);
							}
						}
						else
						{
							m_MainState = State_Skill;
							GC(cAnimation)->SetAnimation("CD");
							AddForce(150, -750);
							PlayVoice(RandomText("Iori_Attack", 1, 5));
						}
					}
					else
					{
						Idle();
					}
				}
				else if (Dist < 300)
				{
					if (Random(0, (int)(1.f / DT)) == 0)
					{
						if (abs(m_Owner->m_Pos.y - m_Target->m_Owner->m_Pos.y) <= 15)
						{
							m_MainState = State_Skill;
							GC(cAnimation)->SetAnimation("Aoi");
							GC(cAnimation)->m_Speed = 0.4;
						}
						else
						{
							m_MainState = State_Skill;
							GC(cAnimation)->SetAnimation("CD");
							AddForce(500, -800);
							PlayVoice(RandomText("Iori_Attack", 1, 5));
						}
					}
					else
					{
						Move();
					}
				}
				else
				{
					if (Random(0, (int)(2.f / DT)) == 0)
					{
						m_MainState = State_Attack;
						GC(cAnimation)->SetAnimation("Yami");
						PlayVoice(RandomText("Iori_Attack", 1, 5));
					}
					else
					{
						Move();
					}
				}
				m_TargetZ = m_Target->m_Owner->m_Z;
			}
			m_Owner->m_Scale.x = Sign(m_Target->m_Owner->m_Pos.x - m_Owner->m_Pos.x);
		}
	}
}

void cIori::Render()
{
	cEnemy::Render();
}

void cIori::Release()
{
	cEnemy::Release();
	OBJECT->m_Boss = nullptr;
}

void cIori::OnCollision(cObject * _Other, RECT _Rect)
{
	cEnemy::OnCollision(_Other, _Rect);
}

void cIori::OnAnimationEnd(string _Key)
{
	cEnemy::OnAnimationEnd(_Key);

	if (_Key == "Aoi" || _Key == "Kuzu_Miss" || _Key == "Kuzu_Hit" || _Key == "Yami" || _Key == "CD")
	{
		Idle();
		return;
	}

	if (_Key == "Kuzu_Start")
	{
		GC(cAnimation)->SetAnimation("Kuzu_Miss");
		PlayVoice("Iori_Kuzu_Miss");
		return;
	}

	if (_Key == "Intro")
	{
		m_Intro = false;
		m_Invincible = false;
		Idle();
		return;
	}
}

void cIori::OnAnimationNotify(string _Key)
{
	if (_Key == "Intro")
	{
		PlayVoice("Iori_Intro");
		return;
	}

	if (_Key == "Aoi_Force1")
	{
		GC(cAnimation)->m_Speed = 1;
		AddForce(300, 0);
		return;
	}
	if (_Key == "Aoi_Attack1")
	{
		AddHitBox(Vec2(20, 30), Vec2(30, -30), 0.1, 30, 0, Vec2(300, 0), 30, 0.5, 0.2, 5);
		PlayVoice(RandomText("Iori_Attack", 1, 5));
		return;
	}
	if (_Key == "Aoi_Attack2")
	{
		AddForce(250, 0);
		AddHitBox(Vec2(20, 30), Vec2(20, -40), 0.1, 30, 0, Vec2(150, -700), 25, 0.5, 0.2, 5);
		PlayVoice(RandomText("Iori_Attack", 1, 5));
		return;
	}
	if (_Key == "Aoi_Force2")
	{
		AddForce(200, -600);
		return;
	}
	if (_Key == "Aoi_Attack3")
	{
		AddHitBox(Vec2(20, 20), Vec2(30, 0), 0.1, 60, 0, Vec2(200, 1000), 20, 0.5, 0.4, 7);
		PlayVoice(RandomText("Iori_Attack", 1, 5));
		return;
	}

	if (_Key == "CD_Attack1")
	{
		AddHitBox(Vec2(30, 20), Vec2(30, 20), 0.1, 75, 0, Vec2(300, -300), 25, 0.5, 0.4, 7);
		return;
	}

	if (_Key == "Yami_Attack1")
	{
		AddHitBox(Vec2(35, 35), Vec2(0, 0), 100, 75, 0, Vec2(300, 0), 30, 0.5, 0.2, 5, "Iori_Hit");
		FireMissile("Iori_Yami_Missile", 0.1, m_Owner->m_Pos + Vec2(0, 40), 500, m_Owner->m_Scale.x == 1 ? 0 : 180)->m_Owner->SetAlarm(0, 10);
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, m_Owner->m_Scale, 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Iori_Yami_Fire");
		Anim->m_Speed = 0.07;
		return;
	}

	if (_Key == "Kuzu_Attack1")
	{
		AddHitBox(Vec2(25, 10), Vec2(25, 40), 0.01, 0, 0, Vec2(0, 0), 40, 10000, 0.3, 5, "Kuzu_Hit", false);
		return;
	}
	if (_Key == "Kuzu_Attack2")
	{
		AddHitBox(Vec2(100, 100), Vec2(0, 0), 0.01, 0, 0, Vec2(-1000, 0), 100, 3, 0.3, 5);
		PlayVoice(RandomText("Iori_Kuzu_Hit", 1, 2));
		return;
	}
}

void cIori::OnHit(string _Key, cObject * _Other, RECT _Rect)
{
	cEnemy::OnHit(_Key, _Other, _Rect);
	if (_Key == "Kuzu_Hit")
	{
		GC(cAnimation)->SetAnimation("Kuzu_Hit");
		_Other->m_Pos = m_Owner->m_Pos + Vec2(20 * m_Owner->m_Scale.x, 0);
		_Other->m_Z = m_Owner->m_Z - 1;
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos + Vec2(20 * m_Owner->m_Scale.x, -30), Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.02);
		Anim->m_Anim = IMAGE->FindAnimation("Throw");
		Anim->m_Speed = 0.005;
		SOUND->Play("Throw1", -500);
		m_Velocity.x = 0;
		_Other->GC(cCharacter)->m_Velocity.x = 0;
		return;
	}
}
