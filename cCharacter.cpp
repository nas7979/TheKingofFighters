#include "DXUT.h"
#include "cCharacter.h"


cCharacter::cCharacter()
{
}


cCharacter::~cCharacter()
{
}

void cCharacter::Init()
{
	AC(cAnimation);
	GC(cAnimation)->AddAnimation("Jump", m_Owner->m_Name + "_Jump", 100);
	GC(cAnimation)->AddAnimation("Hit1", m_Owner->m_Name + "_Hit1_", 1);
	GC(cAnimation)->AddAnimation("Hit2", m_Owner->m_Name + "_Hit2_", 1);
	GC(cAnimation)->AddAnimation("Hit_Air", m_Owner->m_Name + "_Hit_Air", 100);
	GC(cAnimation)->AddAnimation("Fall", m_Owner->m_Name + "_Fall", 100);
	GC(cAnimation)->AddAnimation("Bounce", m_Owner->m_Name + "_Bounce", 100);
	GC(cAnimation)->AddAnimation("Down", m_Owner->m_Name + "_Down", 100);

	AC(cCollider)->m_CollWith.push_back(Obj_Map);

	m_MainState = State_Idle;
	m_SubState = State_Air;
	m_AlwaysSuper = false;
	m_GuardPoint = false;
	m_GuardPointHited = false;
	m_SuperArmor = false;
	m_Invincible = false;
	m_InStun = false;
	m_Velocity = Vec2(0, 0);
	m_Dead = false;
}

void cCharacter::Update()
{
	if (m_SubState == State_Air)
	{
		m_Velocity.y += 1750 * DT;
		if (m_MainState == State_Idle)
		{
			int Size = GC(cAnimation)->m_CurAnim->Size;
			GC(cAnimation)->m_Frame = max(1 + Size - abs(m_Velocity.y / (500 / Size)), 1);
		}
	}
	else
	{
		m_Velocity.x *= pow(0.95, DT * 60);
		if (m_InStun && m_MainState == State_Idle)
		{
			m_MainState = State_Stun;
			SOUND->Play("Stun", -500);
			GC(cAnimation)->SetAnimation("Stun");
			m_InStun = false;
			m_Stun = 10000000;
			m_Invincible = false;
			m_SuperArmor = false;
			m_Owner->SetAlarm(2, 5);
		}

		if (m_Ground != nullptr)
		{
			RECT Rect;
			if (!IntersectRect(&Rect, &GC(cCollider)->m_Rect, &m_Ground->GC(cCollider)->m_Rect) || abs(m_Owner->m_Z - m_Ground->m_Owner->m_Z) > m_Ground->GC(cGround)->m_Z)
			{
				m_Ground = nullptr;
				m_SubState = State_Air;
				if (m_MainState != State_Skill && m_MainState != State_Hit && m_MainState != State_Down && m_Dead == false)
				{
					m_MainState = State_Idle;
					GC(cAnimation)->SetAnimation("Jump");
				}
			}
		}
	}

	if (m_MainState != State_Hit && m_MainState != State_Down)
	{
		m_Stun += 8 * DT;
		if (m_Stun >= m_MaxStun && m_MainState != State_Stun)
		{
			m_Stun = m_MaxStun;
		}
	}

	if (m_Stun <= 0 && m_InStun == false)
	{
		Stun();
	}

	if (m_Hp <= 0 && m_Dead == false)
	{
		Death();
	}

	m_Owner->m_Pos += m_Velocity * DT;
	if (m_Dead == false)
	{
		m_Owner->m_Depth = 0.3 + m_Owner->m_Z * 0.001;
	}
}

void cCharacter::Render()
{
}

void cCharacter::Release()
{
	//if (m_Voice != nullptr)
	//{
	//	m_Voice->Release();
	//	m_Voice = nullptr;
	//}
}

void cCharacter::OnAnimationEnd(string _Key)
{
	if (_Key == "Wake")
	{
		Idle();
	}
}

void cCharacter::OnAnimationNotify(string _Key)
{
}

void cCharacter::OnCollision(cObject * _Other, RECT _Rect)
{
	if (_Other->m_Pos.y + m_Velocity.y * DT + 10 >= m_Owner->m_Pos.y + GC(cCollider)->m_Size.y && abs(m_Owner->m_Z - _Other->m_Z) < _Other->GC(cGround)->m_Z && m_Velocity.y > 0)
	{
		m_Owner->m_Pos.y -= (_Rect.bottom - _Rect.top) - 1;
		m_Ground = _Other->GC(cGround);
		if (m_HitBox != nullptr)
		{
			m_HitBox->m_Owner->m_Destroyed = true;
			m_HitBox = nullptr;
		}
		if (m_SubState == State_Air)
		{
			if (m_MainState == State_Hit)
			{
				SOUND->Play(RandomText("Down", 1, 2), -500);
				if (m_Velocity.y >= 400)
				{
					GC(cAnimation)->SetAnimation("Bounce");
					m_Velocity.y *= -0.5;
					m_Velocity.x *= 0.75;
					cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos + Vec2(0, 50), Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth + 0.01);
					Anim->m_Anim = IMAGE->FindAnimation("Fall_Large");
					Anim->m_Speed = 0.05;
				}
				else
				{
					GC(cAnimation)->SetAnimation("Down");
					m_MainState = State_Down;
					m_SubState = State_Ground;
					m_Owner->SetAlarm(1, Random(0.75f, 1.25f));
					m_Velocity.y = 0;
					m_Velocity.x *= 0.5;
					cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos + Vec2(0, 50), Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth + 0.01);
					Anim->m_Anim = IMAGE->FindAnimation("Fall_Small");
					Anim->m_Speed = 0.05;
				}
			}
			else
			{
				m_SubState = State_Ground;
				m_Velocity = Vec2(0, 0);
				if (m_MainState != State_Skill)
				{
					if (m_SubState == State_Ground)
					{
						GC(cAnimation)->SetAnimation("Idle");
					}
					else
					{
						GC(cAnimation)->SetAnimation("Jump");
					}
					m_MainState = State_Idle;
					if (m_AlwaysSuper && m_InStun == false)
					{
						m_SuperArmor = true;
					}
				}
				SOUND->Play("Land", -500);
			}
		}
	}
}

void cCharacter::OnHit(string _Key, cObject * _Other, RECT _Rect)
{
	if (_Key == "Fire")
	{
		_Other->GC(cRenderer)->SetFire(1);
		SOUND->Play(RandomText("Fire", 1, 3), -500);
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, _Other->m_Pos + Vec2(Random(-30, 30), Random(-40, 40)), Vec2(1, 1), 0, _Other->m_Z, _Other->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation(RandomText("Fire_Large", 1, 3, true));
		Anim->m_Speed = 0.05;
		return;
	}

	if (_Key == "IoriFire")
	{
		_Other->GC(cRenderer)->SetFire(Pal_PurpleFire);
		SOUND->Play(RandomText("Fire", 1, 3), -500);
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, _Other->m_Pos + Vec2(Random(-30, 30), Random(-40, 40)), Vec2(1, 1), 0, _Other->m_Z, _Other->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation(RandomText("Fire_Purple_Large", 1, 3, true));
		Anim->m_Speed = 0.05;
		return;
	}

	if (_Key == "Flash")
	{
		cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Point"), Vec2(0, 0), Vec2(10000, 10000), 0, 0, 0.81);
		Part->SetAlpha(3000, -255 * 600, 1);
		return;
	}

	if (_Key == "FireOff")
	{
		_Other->GC(cRenderer)->SetFire(0);
		return;
	}
}

void cCharacter::Idle()
{
	if (m_MainState != State_Idle)
	{
		if (m_SubState == State_Ground)
		{
			GC(cAnimation)->SetAnimation("Idle");
		}
		else
		{
			GC(cAnimation)->SetAnimation("Jump");
		}
		m_MainState = State_Idle;
	}
	if (m_AlwaysSuper && m_InStun == false)
	{
		m_SuperArmor = true;
	}
}

void cCharacter::Move()
{
	if (m_SubState == State_Ground)
	{
		if (m_MainState != State_Walk)
		{
			GC(cAnimation)->SetAnimation("Walk");
			m_MainState = State_Walk;
		}
		m_Owner->m_Pos.x += m_Owner->m_Scale.x * m_Speed * DT;
		if (abs(m_TargetZ - m_Owner->m_Z) >= 5)
		{
			m_Owner->m_Z += Sign(m_TargetZ - m_Owner->m_Z) * m_Speed * 0.5 * DT;
		}
	}
}

void cCharacter::Jump()
{
	if (m_SubState == State_Ground)
	{
		GC(cAnimation)->SetAnimation("Jump");
		m_MainState = State_Idle;
		m_SubState = State_Air;
		SOUND->Play(m_Speed > 300 ? "Jump_Large" : "Jump", -500);
		m_Velocity.y = -750;
	}
}

void cCharacter::Stun()
{
	m_InStun = true;
	m_Invincible = true;
	m_MainState = State_Hit;
	if (m_SubState == State_Ground)
	{
		AddForce(-200, -500);
		GC(cAnimation)->SetAnimation("Hit_Air");
	}
	else
	{
		GC(cAnimation)->SetAnimation("Hit_Air");
	}
}

void cCharacter::Death()
{
	m_Invincible = true;
	m_Dead = true;
	m_MainState = State_Hit;
	if (m_SubState == State_Ground)
	{
		AddForce(-200, -500);
		GC(cAnimation)->SetAnimation("Hit_Air");
	}
	else
	{
	}
	PlayVoice(m_Owner->m_Name + "_Death", -500);
}

void cCharacter::PlayVoice(string _Key, long _Volume)
{
	if (m_Voice != nullptr)
	{
		m_Voice->Release();
		m_Voice = nullptr;
	}
	m_Voice = SOUND->Play(_Key, -500, false, true);
}

void cCharacter::AddForce(float _X, float _Y)
{
	m_Velocity.x = _X * m_Owner->m_Scale.x;
	if (_Y != 0)
	{
		m_Velocity.y = _Y;
		m_SubState = State_Air;
	}
}

void cCharacter::AddHitBox(Vec2 _Size, Vec2 _Pos, float _Time, float _Damage, float _Stun, Vec2 _Force, float _Z, float _HitTime, float _StopTime, float _Shake, string _Event, bool _DodgeAble, int _EffectSize)
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
	a->GC(cCollider)->m_CollWith.push_back(Obj_Player);
}

cMissile* cCharacter::FireMissile(string _Anim, float _AnimSpeed,  Vec2 _Pos, float _Speed, float _Dir)
{
	cObject* a = OBJECT->AddObject("Missile", _Pos, m_Owner->m_Z, m_Owner->m_Depth, Obj_Missile);
	a->m_Scale = m_Owner->m_Scale;
	a->AC(cMissile)->m_Speed = _Speed;
	a->GC(cMissile)->m_Dir = _Dir;
	a->GC(cMissile)->m_HitBox = m_HitBox;
	a->GC(cMissile)->m_FiredBy = m_Owner;
	m_HitBox->m_Character = a->GC(cMissile);
	m_HitBox = nullptr;
	a->GC(cAnimation)->AddAnimation("Idle", _Anim, _AnimSpeed);
	a->GC(cAnimation)->SetAnimation("Idle");
	return a->GC(cMissile);
}
