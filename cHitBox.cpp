#include "DXUT.h"
#include "cHitBox.h"
#include "cCharacter.h"

cHitBox::cHitBox()
{
}


cHitBox::~cHitBox()
{
}

void cHitBox::Init()
{
	AC(cCollider);
	m_Owner->SetAlarmSize(1);
	m_Owner->m_AlarmFunc = [&](int _Index)->void {
		m_Owner->m_Destroyed = true;
		m_Character->m_HitBox = nullptr;
	};
}

void cHitBox::Update()
{
	m_Owner->m_Pos = m_Character->m_Owner->m_Pos;
	m_Owner->m_Scale = m_Character->m_Owner->m_Scale;
}

void cHitBox::Render()
{
}

void cHitBox::Release()
{
}

void cHitBox::OnCollision(cObject * _Other, RECT _Rect)
{
	if (_Other == m_Character->m_Owner)
		return;
	if (m_Character->GC(cMissile) != nullptr)
	{
		if (m_Character->GC(cMissile)->m_FiredBy == _Other)
			return;
	}
	int Damage = m_Damage *= Random(0.85f, 1.15f);
	if (abs(m_Owner->m_Z - _Other->m_Z) <= m_Z)
	{
		cCharacter* Other = _Other->GC(cCharacter);

		if (Other->m_Invincible || (Other->m_MainState == State_Dodge && m_DodgeAble == true) || m_Character->m_MainState == State_Hit || Other->m_MainState == State_Down)
			return;

		for (auto& iter : m_Hited)
		{
			if (iter == _Other)
				return;
		}
		m_Hited.push_back(_Other);

		if (m_Character->m_SubState == State_Air && m_Character->m_MainState == State_Attack && Other->m_SuperArmor == false)
		{
			Other->m_MainState = State_Idle;
		}

		if (Other->m_MainState == State_Guard || (Other->m_GuardPoint && Damage != 0))
		{
			if (m_Damage == 0 && m_Stun == 0)
			{
				m_Character->OnHit(m_Event, _Other, _Rect);
			}
			SOUND->Play(RandomText("Block", 1, 2), -500);
			cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, Vec2((_Rect.right + _Rect.left) * 0.5f, (_Rect.top + _Rect.bottom) * 0.5f), Vec2(1, 1), 0, m_Owner->m_Z, _Other->m_Depth - 0.01);
			Anim->m_Anim = IMAGE->FindAnimation("Block");
			Anim->m_Speed = 0.05;
			if (Other->m_MainState == State_Guard)
			{
				Other->GC(cAnimation)->SetAnimation("Guard_Hit");
				_Other->SetAlarm(3, Random(0.5f, 1.f));
				_Other->m_Scale.x = -m_Owner->m_Scale.x;
			}
			else
			{
				Other->m_GuardPointHited = true;
				SYSTEM->HitStop(0.5);
			}
		}
		else
		{
			m_Character->OnHit(m_Event, _Other, _Rect);
			if (m_HitTime != 0)
			{
				if (Other->m_SuperArmor)
				{
					Other->m_Hp -= Damage;
					Other->m_Stun -= m_Stun;
					Other->m_Velocity.x += m_Force.x * m_Owner->m_Scale.x;
					SYSTEM->HitStop(m_StopTime);
					CAMERA->Shake(m_Shake, m_StopTime * 1.1);
				}
				else
				{
					if (Other->m_HitBox != nullptr)
					{
						Other->m_HitBox->m_Owner->m_Destroyed = true;
						Other->m_HitBox = nullptr;
					}
					SYSTEM->HitStop(m_StopTime);
					CAMERA->Shake(m_Shake, m_StopTime * 1.1);
					Other->m_Hp -= Damage;
					Other->m_Stun -= m_Stun;
					if (_Other->m_Tag == Obj_Player && m_Character->m_Owner->m_Tag == Obj_Player && m_Stun != 0)
						Other->m_Velocity.x = m_Force.x * m_Owner->m_Scale.x * 1.25;
					else
						Other->m_Velocity.x = m_Force.x * m_Owner->m_Scale.x;
					Other->m_MainState = State_Hit;
					_Other->m_Scale.x = -m_Owner->m_Scale.x;
					if (m_Force.y != 0)
					{
						Other->m_Velocity.y = m_Force.y;
						Other->m_SubState = State_Air;
					}

					if (Other->m_SubState == State_Ground)
					{
						Other->GC(cAnimation)->SetAnimation(RandomText("Hit", 1, 2));
						Other->GC(cAnimation)->m_Speed = Other->GC(cAnimation)->m_CurAnim->Size / m_HitTime;
					}
					else
					{
						if (m_Force.y <= 0)
						{
							Other->GC(cAnimation)->SetAnimation("Hit_Air");
						}
						else
						{
							Other->GC(cAnimation)->SetAnimation("Fall");
						}
					}

				}
				_Other->SetAlarm(0, m_HitTime);
			}
			if (m_Damage != 0)
			{
				if (m_Character->m_Owner->m_Tag == Obj_Player)
				{
					SYSTEM->m_Combo++;
					SYSTEM->m_ComboEnded = false;
					SYSTEM->m_Alarm[1] = 1.5;
					SYSTEM->m_ComboScale = 2;
					SYSTEM->m_Score += Damage * ((float)SYSTEM->m_Combo * 0.05 + 1) * 1000;

					cPlayer* Player;
					if (m_Character->GC(cMissile) == nullptr)
						Player = m_Character->GC(cPlayer);
					else
						Player = m_Character->GC(cMissile)->m_FiredBy->GC(cPlayer);
					Player->m_Dealt += Damage;
					Player->AddGauge(Damage * Sign(m_Stun));
					if (Other->m_Hp <= 0)
					{
						Player->m_Killed++;
						Player->m_Dealt += Other->m_Hp;
					}
					if (_Other->GC(cPlayer) != nullptr)
					{
						_Other->GC(cPlayer)->AddGauge(m_Damage * 2);
					}

					string DamageText = to_string(Damage);
					cParticle* Part;
					Vec2 Pos = Vec2(-5 + Random(-20, 20), Random(-30, 30));
					if (DamageText.size() == 1)
					{
						Part = PART->AddParticle<cParticle>(SYSTEM->m_DamageNumber[DamageText[0] - '0'], _Other->m_Pos + Pos, Vec2(2, 2), 0, _Other->m_Z, 0.29);
						Part->SetPos(Vec2(0, -750), 0.9);
						Part->SetAlpha(500, -255, 1);
					}
					else if (DamageText.size() == 2)
					{
						Part = PART->AddParticle<cParticle>(SYSTEM->m_DamageNumber[DamageText[0] - '0'], _Other->m_Pos + Pos + Vec2(-10, 0), Vec2(2, 2), 0, _Other->m_Z, 0.29);
						Part->SetPos(Vec2(0, -750), 0.9);
						Part->SetAlpha(500, -255, 1);
						Part = PART->AddParticle<cParticle>(SYSTEM->m_DamageNumber[DamageText[1] - '0'], _Other->m_Pos + Pos + Vec2(10, 0), Vec2(2, 2), 0, _Other->m_Z, 0.29);
						Part->SetPos(Vec2(0, -750), 0.9);
						Part->SetAlpha(500, -255, 1);
					}
					else if (DamageText.size() == 3)
					{
						Part = PART->AddParticle<cParticle>(SYSTEM->m_DamageNumber[DamageText[0] - '0'], _Other->m_Pos + Pos + Vec2(-20, 0), Vec2(2, 2), 0, _Other->m_Z, 0.29);
						Part->SetPos(Vec2(0, -750), 0.9);
						Part->SetAlpha(500, -255, 1);
						Part = PART->AddParticle<cParticle>(SYSTEM->m_DamageNumber[DamageText[1] - '0'], _Other->m_Pos + Pos, Vec2(2, 2), 0, _Other->m_Z, 0.29);
						Part->SetPos(Vec2(0, -750), 0.9);
						Part->SetAlpha(500, -255, 1);
						Part = PART->AddParticle<cParticle>(SYSTEM->m_DamageNumber[DamageText[2] - '0'], _Other->m_Pos + Pos + Vec2(20, 0), Vec2(2, 2), 0, _Other->m_Z, 0.29);
						Part->SetPos(Vec2(0, -750), 0.9);
						Part->SetAlpha(500, -255, 1);
					}
				}
				else
				{
					_Other->GC(cPlayer)->AddGauge(Damage * 2);
				}
				Other->PlayVoice(RandomText((char*)string(_Other->m_Name + "_Hit").c_str(), 1, Other->m_HitSound));
				cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, Vec2((_Rect.right + _Rect.left) * 0.5f, (_Rect.top + _Rect.bottom) * 0.5f), Vec2(1, 1), 0, m_Owner->m_Z, _Other->m_Depth - 0.01);
				Anim->m_Speed = 0.05;
				if (m_Size == 0)
				{
					if (Damage < 20)
					{
						Anim->m_Anim = IMAGE->FindAnimation(RandomText("Hit1", 1, 2, true));
						SOUND->Play(RandomText("Hit_Soft", 1, 2), -500);
					}
					else if (Damage < 60)
					{
						Anim->m_Anim = IMAGE->FindAnimation(RandomText("Hit2", 1, 2, true));
						SOUND->Play(RandomText("Hit_Medium", 1, 2), -500);
					}
					else
					{
						Anim->m_Anim = IMAGE->FindAnimation(RandomText("Hit3", 1, 2, true));
						SOUND->Play("Hit_Hard", -500);
					}
				}
				else
				{
					switch (m_Size)
					{
					case 1:
					{
						Anim->m_Anim = IMAGE->FindAnimation(RandomText("Hit1", 1, 2, true));
						SOUND->Play(RandomText("Hit_Soft", 1, 2), -500);
					}
					break;
					case 2:
					{
						Anim->m_Anim = IMAGE->FindAnimation(RandomText("Hit2", 1, 2, true));
						SOUND->Play(RandomText("Hit_Medium", 1, 2), -500);
					}
					break;
					case 3:
					{
						Anim->m_Anim = IMAGE->FindAnimation(RandomText("Hit3", 1, 2, true));
						SOUND->Play("Hit_Hard", -500);
					}
					break;
					case 4:
					{
						Anim->m_Anim = IMAGE->FindAnimation(RandomText("Hit3", 1, 2, true));
						SOUND->Play("Stab1", -500);
					}
					break;
					case 5:
					{
						Anim->m_Anim = IMAGE->FindAnimation(RandomText("Hit3", 1, 2, true));
						SOUND->Play("Stab2", -500);
					}
					break;

					default:
					{
						Anim->m_Anim = IMAGE->FindAnimation(RandomText("Hit3", 1, 2, true));
						Anim->m_Pos = Vec2(-1000, -1000);
						break;
					}
					}
				}
			}
		}
	}
}
