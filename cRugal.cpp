#include "DXUT.h"
#include "cRugal.h"


cRugal::cRugal()
{
}


cRugal::~cRugal()
{
}

void cRugal::Init()
{
	cEnemy::Init();
	GC(cCollider)->Setting(Vec2(30, 60), Vec2(0, 0));
	GC(cRenderer)->m_ShadowOffset = -25;

	GC(cAnimation)->AddAnimation("Idle", m_Owner->m_Name + "_Idle", 0.13);
	GC(cAnimation)->AddAnimation("Walk", m_Owner->m_Name + "_Walk", 0.11);
	GC(cAnimation)->AddAnimation("Wake", m_Owner->m_Name + "_Wake", 0.06);
	GC(cAnimation)->AddAnimation("Intro", m_Owner->m_Name + "_Intro", 0.1);

	GC(cAnimation)->AddAnimation("Beads", m_Owner->m_Name + "_Beads", 0.07);
	GC(cAnimation)->AddNotify("Beads", 6, "Beads_Attack1");
	GC(cAnimation)->AddNotify("Beads", 12, "Beads_Attack2");   
	GC(cAnimation)->AddNotify("Beads", 15, "Beads_Attack3");
	GC(cAnimation)->AddNotify("Beads", 23, "Beads_Speed1");
	GC(cAnimation)->AddNotify("Beads", 26, "Beads_Speed2");
	GC(cAnimation)->AddNotify("Beads", 27, "Beads_Attack4");

	GC(cAnimation)->AddAnimation("Cutter", m_Owner->m_Name + "_Cutter", 0.035);
	GC(cAnimation)->AddNotify("Cutter", 4, "Cutter_Force1");
	GC(cAnimation)->AddNotify("Cutter", 5, "Cutter_Attack1");
	GC(cAnimation)->AddNotify("Cutter", 15, "Cutter_Attack2");
	GC(cAnimation)->AddNotify("Cutter", 33, "Cutter_Attack3");

	GC(cAnimation)->AddAnimation("Kaiser", m_Owner->m_Name + "_Kaiser", 0.05);
	GC(cAnimation)->AddNotify("Kaiser", 34, "Kaiser_Attack1");

	GC(cAnimation)->AddAnimation("Vanishing", "Rugal_Vanishing", 0.08);
	GC(cAnimation)->AddNotify("Vanishing", 8, "Vanishing_Speed1");
	GC(cAnimation)->AddNotify("Vanishing", 9, "Vanishing_Move1");
	GC(cAnimation)->AddNotify("Vanishing", 10, "Vanishing_Attack1");
	GC(cAnimation)->AddNotify("Vanishing", 11, "Vanishing_Attack1");
	GC(cAnimation)->AddNotify("Vanishing", 12, "Vanishing_Attack1");
	GC(cAnimation)->AddNotify("Vanishing", 13, "Vanishing_Move2");
	GC(cAnimation)->AddNotify("Vanishing", 14, "Vanishing_Attack2");
	GC(cAnimation)->AddNotify("Vanishing", 15, "Vanishing_Speed2");

	GC(cAnimation)->AddAnimation("Press_Start", m_Owner->m_Name + "_Press_Start", 0.2);
	GC(cAnimation)->AddAnimation("Press_Run", m_Owner->m_Name + "_Press_Run", 0.1);
	GC(cAnimation)->AddAnimation("Press_Hit", m_Owner->m_Name + "_Press_Hit", 0.05);
	GC(cAnimation)->AddAnimation("Press_Hit_Wall", m_Owner->m_Name + "_Press_Hit_Wall", 0.05);
	GC(cAnimation)->AddNotify("Press_Hit_Wall", 1, "Press_Pos1");
	GC(cAnimation)->AddNotify("Press_Hit_Wall", 2, "Press_Attack1");
	GC(cAnimation)->AddNotify("Press_Hit_Wall", 13, "Press_Force1");
	GC(cAnimation)->AddAnimation("Press_Miss", m_Owner->m_Name + "_Press_Miss", 0.1);

	GC(cAnimation)->SetAnimation("Intro");
	OBJECT->m_Boss = m_Owner;
	m_Intro = true;
	m_Invincible = true;
	m_AlwaysSuper = true;

	m_MaxHp = 1500;
	m_Hp = m_MaxHp;

	m_MaxStun = 150;
	m_Stun = m_MaxStun;

	m_HitSound = 3;
	m_Speed = 150;
	m_MainState = State_Skill;
	m_PressHited = nullptr;
}

void cRugal::Update()
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
					if (Dist <= 100 && abs(m_TargetZ - m_Owner->m_Z) < 5)
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
					if (Random(0, (int)(0.75f / DT)) == 0)
					{
						if (abs(m_Owner->m_Pos.y - m_Target->m_Owner->m_Pos.y) <= 15)
						{
							if (Random(0, 1) == 0)
							{
								m_MainState = State_Skill;
								GC(cAnimation)->SetAnimation("Beads");
								GC(cAnimation)->m_Speed = 0.5;
							}
							else
							{
								m_MainState = State_Skill;
								GC(cAnimation)->SetAnimation("Vanishing");
								cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
								Anim->m_Anim = IMAGE->FindAnimation("Flash");
								Anim->m_Speed = 0.05;
								SOUND->Play("Flash", -500);
							}

						}
						else
						{
							m_MainState = State_Skill;
							GC(cAnimation)->SetAnimation("Cutter");
							PlayVoice("Rugal_Cutter");
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
						if (Random(0, 2) == 0)
						{
							m_MainState = State_Skill;
							GC(cAnimation)->SetAnimation("Vanishing");
							cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
							Anim->m_Anim = IMAGE->FindAnimation("Flash");
							Anim->m_Speed = 0.05;
							SOUND->Play("Flash", -500);
						}
						else
						{
							m_MainState = State_Skill;
							GC(cAnimation)->SetAnimation("Press_Start");
							PlayVoice("Rugal_Press_Start");
							cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
							Anim->m_Anim = IMAGE->FindAnimation("Flash");
							Anim->m_Speed = 0.05;
							SOUND->Play("Flash", -500);
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
						m_MainState = State_Skill;
						GC(cAnimation)->SetAnimation("Kaiser");
						PlayVoice("Rugal_Kaiser_Start");
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

	if (GC(cAnimation)->m_CurAnim->Key == "Press_Run" && m_HitBox != nullptr)
	{
		m_Owner->m_Pos.x += 600 * m_Owner->m_Scale.x * DT;
		if (Sign(m_Target->m_Owner->m_Pos.x - m_Owner->m_Pos.x) != m_Owner->m_Scale.x)
		{
			GC(cAnimation)->SetAnimation("Press_Miss");
			AddForce(200, 0);
			m_HitBox->m_Owner->m_Destroyed = true;
			m_HitBox = nullptr;
		}
	}

	if (GC(cAnimation)->m_CurAnim->Key == "Press_Hit")
	{
		m_PressHited->m_Pos = m_Owner->m_Pos + Vec2(-40 * m_Owner->m_Scale.x, 0);
		m_PressHited->GC(cCharacter)->m_Invincible = true;
		m_PressHited->GC(cCharacter)->m_SubState = State_Ground;
		m_Owner->m_Pos.x += 600 * m_Owner->m_Scale.x * DT;
		if ((abs(m_Owner->m_Pos.x - CAMERA->m_Pos.x - 480) <= 125 && m_Owner->m_Scale.x == 1) || (abs(m_Owner->m_Pos.x - CAMERA->m_Pos.x + 480) <= 125 && m_Owner->m_Scale.x == -1))
		{
			GC(cAnimation)->SetAnimation("Press_Hit_Wall");
		}
	}
}

void cRugal::Render()
{
	cEnemy::Render();
}

void cRugal::Release()
{
	cEnemy::Release();
	OBJECT->m_Boss = nullptr;
}

void cRugal::OnCollision(cObject * _Other, RECT _Rect)
{
	cEnemy::OnCollision(_Other, _Rect);
}

void cRugal::OnAnimationEnd(string _Key)
{
	cEnemy::OnAnimationEnd(_Key);

	if (_Key == "Beads" || _Key == "Kaiser" || _Key == "Press_Miss" || _Key == "Press_Hit_Wall" || _Key == "Cutter" || _Key == "Vanishing")
	{
		Idle();
		return;
	}

	if (_Key == "Press_Start")
	{
		GC(cAnimation)->SetAnimation("Press_Run");
		AddHitBox(Vec2(40, 1), Vec2(20, 20), 100, 0, 0, Vec2(0, 0), 40, 100000, 0.3, 7, "Press_Hit", false);
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

void cRugal::OnAnimationNotify(string _Key)
{
	if (_Key == "Beads_Attack1")
	{
		GC(cAnimation)->m_Speed = 1;
		AddForce(400, 0);
		AddHitBox(Vec2(50, 25), Vec2(20, 10), 0.1, 20, 0, Vec2(300, 0), 30, 0.75, 0.2, 5);
		PlayVoice("Rugal_Beads_Start");
		return;
	}
	if (_Key == "Beads_Attack2")
	{
		AddHitBox(Vec2(25, 50), Vec2(25, -10), 0.1, 20, 0, Vec2(100, 1000), 25, 0.75, 0.2, 5);
		return;
	}
	if (_Key == "Beads_Attack3")
	{
		AddHitBox(Vec2(25, 50), Vec2(35, -10), 0.1, 20, 0, Vec2(0, -900), 20, 0.75, 0.25, 6);
		return;
	}
	if (_Key == "Beads_Speed1")
	{
		GC(cAnimation)->m_Speed = 0.5;
		return;
	}
	if (_Key == "Beads_Speed2")
	{
		GC(cAnimation)->m_Speed = 1;
		return;
	}
	if (_Key == "Beads_Attack4")
	{
		AddHitBox(Vec2(30, 40), Vec2(50, -30), 0.15, 70, 0, Vec2(100, 1250), 20, 0.75, 0.5, 8);
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, m_Owner->m_Scale, 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Rugal_Beads_Effect");
		Anim->m_Speed = 0.04;
		PlayVoice("Rugal_Beads_End");
		return;
	}

	if (_Key == "Cutter_Force1")
	{
		GC(cAnimation)->m_Speed = 1;
		AddForce(0, -700);
		return;
	}
	if (_Key == "Cutter_Attack1")
	{
		AddHitBox(Vec2(50, 50), Vec2(15, -10), 0.1, 20, 0, Vec2(0, -600), 30, 1, 0.3, 6);
		return;
	}
	if (_Key == "Cutter_Attack2")
	{
		AddForce(0, -800);
		AddHitBox(Vec2(20, 50), Vec2(30, -10), 0.1, 20, 0, Vec2(0, -700), 30, 1, 0.3, 6);
		return;
	}
	if (_Key == "Cutter_Attack3")
	{
		AddHitBox(Vec2(50, 50), Vec2(25, -10), 0.1, 60, 0, Vec2(0, 1000), 30, 1, 0.3, 6);
		AddForce(-300, 0);
		PlayVoice("Rugal_Cutter_End");
		return;
	}

	if (_Key == "Press_Pos1")
	{
		m_PressHited->m_Pos = m_Owner->m_Pos + Vec2(30 * m_Owner->m_Scale.x, 0);
		PlayVoice("Rugal_Press_Hit_Wall");
		m_PressHited->GetComponent<cCharacter>()->m_Invincible = false;
		return;
	}
	if (_Key == "Press_Attack1")
	{
		m_PressHited->m_Pos = m_Owner->m_Pos + Vec2(110 * m_Owner->m_Scale.x, 0);
		AddHitBox(Vec2(100, 100), Vec2(0, 0), 0.1, 150, 0, Vec2(0, -800), 30, 1, 0.5, 9);
		SOUND->Play("Explosion2", -500);
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos + Vec2(110 * m_Owner->m_Scale.x, -250), Vec2(1, 3), 0, m_Owner->m_Z, m_Owner->m_Depth + 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Rugal_Press_Hit_Wall_Effect");
		Anim->m_Speed = 0.05;
		cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Point"), Vec2(0, 0), Vec2(10000, 10000), 0, 0, 0.8, 0xff000000);
		Part->SetAlpha(1500, -255 * 300, 1);
		Part = PART->AddParticle<cParticle>(IMAGE->Find("Point"), Vec2(0, 0), Vec2(10000, 10000), 0, 0, 0.81);
		Part->SetAlpha(3000, -255 * 300, 1);
		m_PressHited = nullptr;
		return;
	}
	if (_Key == "Press_Force1")
	{
		GC(cAnimation)->m_Speed = 0.2;
		AddForce(-200, -600);
		return;
	}

	if (_Key == "Kaiser_Attack1")
	{
		AddHitBox(Vec2(35, 35), Vec2(0, 0), 100, 100, 0, Vec2(-200, -1000), 35, 1, 0.3, 7);
		FireMissile("Rugal_Kaiser_Missile", 0.1, m_Owner->m_Pos + Vec2(100 * m_Owner->m_Scale.x, 0), 600, m_Owner->m_Scale.x == 1 ? 0 : 180);
		PlayVoice("Rugal_Kaiser_Fire");
		SOUND->Play("Rugal_Kaiser_Fire_Effect", -500);
		return;
	}

	if (_Key == "Vanishing_Speed1")
	{
		GC(cAnimation)->m_Speed = 2;
		SOUND->Play("Rugal_Vanishing_Effect", -500);
		return;
	}
	if (_Key == "Vanishing_Move1")
	{
		m_Owner->m_Pos.x += 150 * m_Owner->m_Scale.x;
		AddHitBox(Vec2(75, 30), Vec2(-75, 0), 0.01, 10, 0, Vec2(Random(-100, 100), 0), 30, 0.1, 0.1, 4, "", false);
		return;
	}
	if (_Key == "Vanishing_Attack1")
	{
		AddHitBox(Vec2(75, 30), Vec2(-75, 0), 0.01, 10, 0, Vec2(Random(-100, 100), 0), 30, 0.1, 0.1, 4, "", false);
		return;
	}
	if (_Key == "Vanishing_Move2")
	{
		m_Owner->m_Pos.x += 150 * m_Owner->m_Scale.x;
		AddHitBox(Vec2(150, 30), Vec2(-150, 0), 0.01, 10, 0, Vec2(Random(-100, 100), 0), 30, 0.1, 0.1, 4, "", false);
		return;
	}
	if (_Key == "Vanishing_Attack2")
	{
		AddHitBox(Vec2(150, 30), Vec2(-150, 0), 0.01, 60, 0, Vec2(Random(-200, 200), -750), 30, 0.1, 0.3, 6, "", false);
		return;
	}
	if (_Key == "Vanishing_Speed2")
	{
		GC(cAnimation)->m_Speed = 0.5;
		PlayVoice("Rugal_Vanishing");
		return;
	}
}

void cRugal::OnHit(string _Key, cObject * _Other, RECT _Rect)
{
	cEnemy::OnHit(_Key, _Other, _Rect);
	if (_Key == "Press_Hit")
	{
		GC(cAnimation)->SetAnimation("Press_Hit");
		_Other->m_Pos = m_Owner->m_Pos + Vec2(-40 * m_Owner->m_Scale.x, 0);
		_Other->m_Z = m_Owner->m_Z - 1;
		SOUND->Play("Throw1", -500);
		PlayVoice("Rugal_Press_Hit");
		m_HitBox->m_Owner->m_Destroyed = true;
		m_HitBox = nullptr;
		m_PressHited = _Other;
		return;
	}
}