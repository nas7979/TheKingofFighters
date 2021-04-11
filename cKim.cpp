#include "DXUT.h"
#include "cKim.h"
#include "cEnemy.h"


cKim::cKim()
{
}


cKim::~cKim()
{
}

void cKim::Init()
{
	cPlayer::Init();
	GC(cCollider)->Setting(Vec2(30, 50), Vec2(0, 0));
	GC(cRenderer)->m_ShadowOffset = -25;

	GC(cAnimation)->AddAnimation("Idle", m_Owner->m_Name + "_Idle", 0.07);
	GC(cAnimation)->AddAnimation("Walk", m_Owner->m_Name + "_Walk", 0.14);
	GC(cAnimation)->AddAnimation("Run", m_Owner->m_Name + "_Run", 0.08);
	GC(cAnimation)->AddAnimation("Wake", m_Owner->m_Name + "_Wake", 0.07);
	GC(cAnimation)->AddAnimation("Dodge", m_Owner->m_Name + "_Dodge", 0.0771f);

	GC(cAnimation)->AddAnimation("WPunch", m_Owner->m_Name + "_WPunch", 0.07);
	GC(cAnimation)->AddNotify("WPunch", 2, "WPunch_Attack1");
	GC(cAnimation)->AddAnimation("WKick", m_Owner->m_Name + "_WKick", 0.05);
	GC(cAnimation)->AddNotify("WKick", 4, "WKick_Attack1");
	GC(cAnimation)->AddAnimation("SPunch", m_Owner->m_Name + "_SPunch", 0.08);
	GC(cAnimation)->AddNotify("SPunch", 3, "SPunch_Attack1");
	GC(cAnimation)->AddNotify("SPunch", 6, "SPunch_Attack2");
	GC(cAnimation)->AddAnimation("SKick", m_Owner->m_Name + "_SKick", 0.07);
	GC(cAnimation)->AddNotify("SKick", 5, "SKick_Attack1");

	GC(cAnimation)->AddAnimation("WPunch_Air", m_Owner->m_Name + "_WPunch_Air", 0.11);
	GC(cAnimation)->AddNotify("WPunch_Air", 2, "WPunch_Air_Attack1");
	GC(cAnimation)->AddAnimation("WKick_Air", m_Owner->m_Name + "_WKick_Air", 0.11);
	GC(cAnimation)->AddNotify("WKick_Air", 2, "WKick_Air_Attack1");
	GC(cAnimation)->AddAnimation("SPunch_Air", m_Owner->m_Name + "_SKick_Air", 0.07);
	GC(cAnimation)->AddNotify("SPunch_Air", 5, "SPunch_Air_Attack1");
	GC(cAnimation)->AddAnimation("SKick_Air", m_Owner->m_Name + "_SPunch_Air", 0.06);
	GC(cAnimation)->AddNotify("SKick_Air", 9, "SKick_Air_Attack1");

	GC(cAnimation)->AddAnimation("GuardCancel", m_Owner->m_Name + "_GuardCancel", 0.04);
	GC(cAnimation)->AddNotify("GuardCancel", 8, "GuardCancel_Attack1");

	GC(cAnimation)->AddAnimation("Hangetsuzan", m_Owner->m_Name + "_Hangetsuzan", 0.06);
	GC(cAnimation)->AddNotify("Hangetsuzan", 3, "Hangetsuzan_Force1");
	GC(cAnimation)->AddNotify("Hangetsuzan", 6, "Hangetsuzan_Attack1");
	GC(cAnimation)->AddNotify("Hangetsuzan", 7, "Hangetsuzan_Attack1");
	GC(cAnimation)->AddNotify("Hangetsuzan", 9, "Hangetsuzan_Attack2");

	GC(cAnimation)->AddAnimation("Hangetsuzan_Air", m_Owner->m_Name + "_Hangetsuzan_Air", 0.045);
	GC(cAnimation)->AddNotify("Hangetsuzan_Air", 3, "Hangetsuzan_Air_Force1");
	GC(cAnimation)->AddNotify("Hangetsuzan_Air", 7, "Hangetsuzan_Air_Attack1");
	GC(cAnimation)->AddNotify("Hangetsuzan_Air", 9, "Hangetsuzan_Air_Attack2");

	GC(cAnimation)->AddAnimation("Hienzan", m_Owner->m_Name + "_Hienzan", 0.06);
	GC(cAnimation)->AddNotify("Hienzan", 3, "Hienzan_Force1");
	GC(cAnimation)->AddNotify("Hienzan", 4, "Hienzan_Attack1");
	GC(cAnimation)->AddNotify("Hienzan", 5, "Hienzan_Attack1");
	GC(cAnimation)->AddNotify("Hienzan", 6, "Hienzan_Attack2");

	GC(cAnimation)->AddAnimation("Tensouzan", m_Owner->m_Name + "_Tensouzan", 0.06);
	GC(cAnimation)->AddNotify("Tensouzan", 4, "Tensouzan_Attack1");

	GC(cAnimation)->AddAnimation("Hisyokyaku_Start", m_Owner->m_Name + "_Hisyokyaku_Start", 0.1);

	GC(cAnimation)->AddAnimation("Hisyokyaku", m_Owner->m_Name + "_Hisyokyaku", 0.08);
	GC(cAnimation)->AddNotify("Hisyokyaku", 1, "Hisyokyaku_Attack1");
	GC(cAnimation)->AddNotify("Hisyokyaku", 2, "Hisyokyaku_Attack1");
	GC(cAnimation)->AddNotify("Hisyokyaku", 3, "Hisyokyaku_Attack1");
	GC(cAnimation)->AddNotify("Hisyokyaku", 4, "Hisyokyaku_Attack1");

	GC(cAnimation)->AddAnimation("Hisyokyaku_End", m_Owner->m_Name + "_Hisyokyaku_End", 0.05);

	GC(cAnimation)->AddAnimation("Sanengeki1", m_Owner->m_Name + "_Sanengeki1_", 0.07);
	GC(cAnimation)->AddNotify("Sanengeki1", 2, "Sanengeki1_Force1");
	GC(cAnimation)->AddNotify("Sanengeki1", 4, "Sanengeki1_Attack1");
	GC(cAnimation)->AddNotify("Sanengeki1", 7, "Sanengeki1_Cancel1");

	GC(cAnimation)->AddAnimation("Sanengeki2", m_Owner->m_Name + "_Sanengeki2_", 0.07);
	GC(cAnimation)->AddNotify("Sanengeki2", 4, "Sanengeki2_Attack1");
	GC(cAnimation)->AddNotify("Sanengeki2", 7, "Sanengeki2_Cancel1");

	GC(cAnimation)->AddAnimation("Sanengeki3", m_Owner->m_Name + "_Sanengeki3_", 0.04);
	GC(cAnimation)->AddNotify("Sanengeki3", 3, "Sanengeki3_Attack1");
	GC(cAnimation)->AddNotify("Sanengeki3", 9, "Sanengeki3_Attack2");

	GC(cAnimation)->AddAnimation("Houkyaku_Start", m_Owner->m_Name + "_Houkyaku_Start", 0.075);
	GC(cAnimation)->AddNotify("Houkyaku_Start", 7, "Houkyaku_Start1");

	GC(cAnimation)->AddAnimation("Houkyaku_Charge", m_Owner->m_Name + "_Houkyaku_Charge", 0.06);

	GC(cAnimation)->AddAnimation("Houkyaku_End", m_Owner->m_Name + "_Houkyaku_End", 0.06);

	GC(cAnimation)->AddAnimation("Houkyaku_Miss", m_Owner->m_Name + "_Houkyaku_Miss", 0.75);

	GC(cAnimation)->AddAnimation("Houkyaku", m_Owner->m_Name + "_Houkyaku", 0.025);
	GC(cAnimation)->AddNotify("Houkyaku", 2, "Houkyaku_Attack1");
	GC(cAnimation)->AddNotify("Houkyaku", 4, "Houkyaku_Attack1");
	GC(cAnimation)->AddNotify("Houkyaku", 8, "Houkyaku_Attack1");
	GC(cAnimation)->AddNotify("Houkyaku", 13, "Houkyaku_Attack1");
	GC(cAnimation)->AddNotify("Houkyaku", 20, "Houkyaku_Attack1");
	GC(cAnimation)->AddNotify("Houkyaku", 25, "Houkyaku_Attack1");
	GC(cAnimation)->AddNotify("Houkyaku", 29, "Houkyaku_Attack1");
	GC(cAnimation)->AddNotify("Houkyaku", 35, "Houkyaku_Attack1");
	GC(cAnimation)->AddNotify("Houkyaku", 39, "Houkyaku_Attack1");
	GC(cAnimation)->AddNotify("Houkyaku", 40, "Houkyaku_Attack1");
	GC(cAnimation)->AddNotify("Houkyaku", 44, "Houkyaku_Attack1");
	GC(cAnimation)->AddNotify("Houkyaku", 52, "Houkyaku_Attack1");
	GC(cAnimation)->AddNotify("Houkyaku", 59, "Houkyaku_Force1");
	GC(cAnimation)->AddNotify("Houkyaku", 60, "Houkyaku_Attack2");
	GC(cAnimation)->AddNotify("Houkyaku", 61, "Houkyaku_Attack2");
	GC(cAnimation)->AddNotify("Houkyaku", 67, "Houkyaku_Attack2");
	GC(cAnimation)->AddNotify("Houkyaku", 68, "Houkyaku_Attack2");
	GC(cAnimation)->AddNotify("Houkyaku", 71, "Houkyaku_Attack2");
	GC(cAnimation)->AddNotify("Houkyaku", 72, "Houkyaku_Attack2");
	GC(cAnimation)->AddNotify("Houkyaku", 77, "Houkyaku_Attack2");
	GC(cAnimation)->AddNotify("Houkyaku", 83, "Houkyaku_Attack3");


	GC(cAnimation)->SetAnimation("Idle");
	m_MaxHp = SYSTEM->m_PlayerRemain == 1 ? 1500 : 750;
	m_Hp = m_MaxHp;
	m_MaxStun = 100000;
	m_Stun = 100000;
	m_SanengekiPhase = 0;
	m_HitSound = 3;
	m_Shift = false;
	m_CancelAble = false;
	m_Killed = 0;
	m_Dealt = 0;
	m_Damage = 1;

	m_Owner->SetAlarmSize(9);
	m_Owner->SetAlarm(8, 0);
	m_Owner->m_AlarmFunc = [&](int _Index)->void {
		switch (_Index)
		{
		case 0:
			if (m_MainState == State_Hit && m_SubState == State_Ground)
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

		case 4:
			m_CancelAble = false;
			break;

		case 5:
			m_GuardPoint = false;
			break;

		case 6:
			if (GC(cAnimation)->m_CurAnim->Key == "Houkyaku")
			{
				if (GC(cAnimation)->m_Frame < 50)
				{
					PlayVoice("Kim_Ata");
					m_Owner->SetAlarm(6, 0.3);
				}
				else
				{
					PlayVoice("Kim_Attack4");
				}
			}
			break;

		case 7:
			m_Hp = m_MaxHp;
			m_Shift = false;
			m_CancelAble = false;
			m_SubState = State_Air;
			Idle();
			m_GuardPoint = false;
			m_GuardPointHited = false;
			m_SuperArmor = false;
			m_Invincible = false;
			m_Velocity = Vec2(0, 0);
			m_Dead = false;

			m_Owner->m_Pos = Vec2(CAMERA->m_Pos.x, -500);
			m_Owner->m_Z = 75;
			SYSTEM->m_PlayerRemain++;
			break;

		case 8:
			string Key = GC(cAnimation)->m_CurAnim->Key;
			if (Key == "Houkyaku_Charge" || Key == "Houkyaku_End" || (Key == "Houkyaku" && GC(cAnimation)->m_Frame >= 59))
			{
				cObject* a = OBJECT->AddObject("AfterImage", m_Owner->m_Pos, m_Owner->m_Z, m_Owner->m_Depth + 0.01f, Obj_None);
				a->m_Scale = m_Owner->m_Scale;
				a->AC(cRenderer)->m_Image = GC(cRenderer)->m_Image;
				a->GC(cRenderer)->SetFire(Pal_AfterImage);
				a->GC(cRenderer)->m_ShadowOffset = 1000000;
				a->SetAlarmSize(1);
				a->m_AlarmFunc = [=](int _Index)->void {
					a->m_Destroyed = true;
				};
				a->SetAlarm(0, 0.2f);
			}
			m_Owner->SetAlarm(8, 0.08f);
			break;
		}
	};
}

void cKim::Update()
{
	if (GC(cAnimation)->m_CurAnim->Key == "Hisyokyaku_Start")
	{
		m_Owner->m_Pos.y -= m_Velocity.y * DT;
		m_Velocity.y = 0;
		if (INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_Left]))
		{
			m_Owner->m_Scale.x = -1;
		}
		if (INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_Right]))
		{
			m_Owner->m_Scale.x = 1;
		}
	}
	else if (GC(cAnimation)->m_CurAnim->Key == "Hisyokyaku")
	{
		m_Velocity.y = 550;
	}
	else if (GC(cAnimation)->m_CurAnim->Key == "Houkyaku_Charge")
	{
		if (abs(m_Velocity.x) <= 200)
		{
			GC(cAnimation)->SetAnimation("Houkyaku_Miss");
			if (m_HitBox != nullptr)
			{
				m_HitBox->m_Owner->m_Destroyed = true;
				m_HitBox = nullptr;
			}
		}
		if (m_SubState == State_Air)
		{
			m_Velocity.y -= 1300 * DT;
		}
	}
	else if (GC(cAnimation)->m_CurAnim->Key == "Houkyaku")
	{
		if (GC(cAnimation)->m_Frame < 58)
		{
			AddForce(75, 0);
		}
		else if (GC(cAnimation)->m_Frame < 82)
		{
			m_Velocity.x *= 0.99f;
			m_Velocity.y = -275;
		}
	}

	cPlayer::Update();

	if ((m_MainState == State_Idle || m_MainState == State_Walk || m_MainState == State_Run) || (m_CancelAble && m_MainState != State_Skill))
	{
		if (m_GaugeStock != 0)
		{
			if (INPUT->CheckCommand(Cmd_2624, Key_WKick, m_Side) || INPUT->CheckCommand(Cmd_2624, Key_SKick, m_Side))
			{
				if (m_SubState == State_Ground && (m_MainState == State_Idle || m_MainState == State_Walk || m_MainState == State_Run))
				{
					m_Owner->m_Scale.x *= -1;
				}
				m_GaugeStock--;
				GC(cAnimation)->SetAnimation("Houkyaku_Start");
				PlayVoice("Kim_Hou");
				cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
				Anim->m_Anim = IMAGE->FindAnimation("Flash");
				Anim->m_Speed = 0.035;
				SOUND->Play("Flash", 0);
				m_MainState = State_Skill;
			}
		}

		if (INPUT->CheckCommand(Cmd_426, Key_WKick, m_Side) || INPUT->CheckCommand(Cmd_426, Key_SKick, m_Side))
		{
			if (m_SubState == State_Ground)
			{
				GC(cAnimation)->SetAnimation("Hangetsuzan");
				m_MainState = State_Skill;
			}
			else
			{
				GC(cAnimation)->SetAnimation("Hangetsuzan_Air");
				m_MainState = State_Skill;
			}
			PlayVoice("Kim_Hangetsuzan");
		}

		if (INPUT->CheckCommand(Cmd_626, Key_WKick, m_Side) || INPUT->CheckCommand(Cmd_626, Key_SKick, m_Side))
		{
			if (m_SubState == State_Ground)
			{
				GC(cAnimation)->SetAnimation("Hienzan");
				m_MainState = State_Skill;
				PlayVoice("Kim_Hienzan");
			}
		}

		if (INPUT->CheckCommand(Cmd_26, Key_WPunch, m_Side) || INPUT->CheckCommand(Cmd_26, Key_SPunch, m_Side))
		{
			if (m_SubState == State_Ground)
			{
				GC(cAnimation)->SetAnimation("Sanengeki1");
				m_SanengekiPhase = 1;
				PlayVoice("Kim_Attack3");
				m_MainState = State_Skill;
			}
		}

		if (INPUT->CheckCommand(Cmd_26, Key_WKick, m_Side) || INPUT->CheckCommand(Cmd_26, Key_SKick, m_Side))
		{
			if(m_SubState == State_Air)
			{
				GC(cAnimation)->SetAnimation("Hisyokyaku_Start");
				PlayVoice("Kim_Hisyokyaku");
				m_MainState = State_Skill;
				m_Velocity.x = 0;
			}
		}
	}

	if (m_MainState == State_Idle || m_MainState == State_Walk || m_MainState == State_Run)
	{
		if (m_SubState == State_Ground)
		{
			bool Moved = false;

			if (INPUT->CheckCommand(Cmd_66, Key_End, m_Side) || INPUT->CheckCommand(Cmd_22, Key_End, m_Side) || INPUT->CheckCommand(Cmd_88, Key_End, m_Side))
			{
				m_Shift = true;
				m_Speed = 350;
			}
			if (m_Shift == false)
			{
				m_Speed = 150;
			}
			if (INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_Left]))
			{
				Moved = true;
				m_Owner->m_Pos.x -= m_Speed * DT;
				m_Owner->m_Scale.x = -1;
			}
			if (INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_Right]))
			{
				Moved = true;
				m_Owner->m_Pos.x += m_Speed * DT;
				m_Owner->m_Scale.x = 1;
			}
			if (INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_Up]) && m_Owner->m_Z < 150)
			{
				Moved = true;
				m_Owner->m_Z += m_Speed * 0.75 * DT;
			}
			if (INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_Down]) && m_Owner->m_Z > 0)
			{
				Moved = true;
				m_Owner->m_Z -= m_Speed * 0.75 * DT;
			}

			if (Moved)
			{
				if (m_Shift)
				{
					if (m_MainState != State_Run)
					{
						GC(cAnimation)->SetAnimation("Run");
						m_MainState = State_Run;
					}
				}
				else
				{
					if (m_MainState != State_Walk)
					{
						GC(cAnimation)->SetAnimation("Walk");
						m_MainState = State_Walk;
					}
				}
			}
			else
			{
				Idle();
				m_Speed = 0;
				m_Shift = false;
			}

			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_Jump]))
			{
				Jump();
				m_Velocity.x = m_Speed * m_Owner->m_Scale.x;
			}

			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_WPunch]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("WPunch");
				PlayVoice("Kim_Attack1");
			}
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_WKick]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("WKick");
				PlayVoice("Kim_Attack1");
			}
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_SPunch]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("SPunch");
				PlayVoice("Kim_Attack2");
			}
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_SKick]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("SKick");
				PlayVoice("Kim_Attack2");
			}

			if (INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_WPunch]) && INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_WKick]))
			{
				GC(cAnimation)->SetAnimation("Dodge");
				AddForce(500, 0);
				PlayVoice("Kim_Attack1");
				m_MainState = State_Dodge;
			}
		}
		else
		{
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_WPunch]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("WPunch_Air");
				PlayVoice("Kim_Attack1");
			}
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_WKick]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("WKick_Air");
				PlayVoice("Kim_Attack1");
			}
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_SPunch]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("SPunch_Air");
				PlayVoice("Kim_Attack2");
			}
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_SKick]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("SKick_Air");
				PlayVoice("Kim_Attack2");
			}
		}
	}

	if (m_MainState == State_Hit && m_SubState == State_Ground && m_GaugeStock != 0 && m_Invincible == false)
	{
		if (INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_SPunch]) && INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_SKick]))
		{
			m_GaugeStock--;
			m_Velocity.x = 0;
			m_MainState = State_Skill;
			GC(cAnimation)->SetAnimation("GuardCancel");
			PlayVoice("Kim_GuardCancel");
			SYSTEM->HitStop(0.5);
			m_GuardPoint = true;
			m_Owner->SetAlarm(5, 0.25);
			cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, m_Owner->m_Scale, 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
			Anim->m_Anim = IMAGE->FindAnimation("GuardCancel");
			Anim->m_Speed = 0.005;
			cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Point"), Vec2(0, 0), Vec2(10000, 10000), 0, 0, 0.8);
			Part->SetAlpha(1000, -255 * 30 * 10, 1);
		}
	}

	if (m_SanengekiPhase != 0)
	{
		if (m_SanengekiPhase == 2 && (INPUT->CheckCommand(Cmd_26, Key_WPunch, m_Side) || INPUT->CheckCommand(Cmd_26, Key_SPunch, m_Side)))
		{
			m_SanengekiPhase = 3;
		}
		else if (m_SanengekiPhase == 5 && (INPUT->CheckCommand(Cmd_26, Key_WPunch, m_Side) || INPUT->CheckCommand(Cmd_26, Key_SPunch, m_Side)))
		{
			m_SanengekiPhase = 6;
		}
	}

	if(!m_Dead)
		m_Owner->m_Pos.x = Clamp(m_Owner->m_Pos.x, CAMERA->m_Pos.x - 960 / CAMERA->m_Scale, CAMERA->m_Pos.x + 960 / CAMERA->m_Scale);
}

void cKim::Render()
{
	cPlayer::Render();
}

void cKim::Release()
{
	cCharacter::Release();
	SYSTEM->m_Player[m_Side] = nullptr;
	if (m_Dead == false)
		SYSTEM->m_PlayerRemain--;
}

void cKim::OnCollision(cObject * _Other, RECT _Rect)
{
	if (_Other->m_Pos.y + m_Velocity.y * DT + 10 >= m_Owner->m_Pos.y + GC(cCollider)->m_Size.y && abs(m_Owner->m_Z - _Other->m_Z) < _Other->GC(cGround)->m_Z && m_Velocity.y > 0)
	{
		if (GC(cAnimation)->m_CurAnim->Key == "Hisyokyaku")
		{
			GC(cAnimation)->SetAnimation("Hisyokyaku_End");
		}
		if (GC(cAnimation)->m_CurAnim->Key == "Houkyaku_Charge" && m_SubState == State_Air)
		{
			GC(cAnimation)->SetAnimation("Houkyaku_Miss");
			m_HitBox->m_Owner->m_Destroyed = true;
			m_HitBox = nullptr;
			AddForce(200, 0);
		}
	}
	cPlayer::OnCollision(_Other, _Rect);
}

void cKim::OnAnimationEnd(string _Key)
{
	cPlayer::OnAnimationEnd(_Key);
	
	if (_Key == "WPunch" || _Key == "WKick" || _Key == "SPunch" || _Key == "SKick" || _Key == "WPunch_Air" || _Key == "WKick_Air" || _Key == "SPunch_Air" || _Key == "SKick_Air" ||
		_Key == "Dodge" || _Key == "GuardCancel" || _Key == "Hangetsuzan" || _Key == "Hangetsuzan_Air" || _Key == "Hienzan" || _Key == "Hisyokyaku_End" ||
		_Key == "Sanengeki1" || _Key == "Sanengeki2" || _Key == "Sanengeki3" || _Key == "Houkyaku_Miss")
	{
		Idle();
		return;
	}

	if (_Key == "Hisyokyaku_Start")
	{
		GC(cAnimation)->SetAnimation("Hisyokyaku");
		AddForce(300, 0);
		return;
	}

	if (_Key == "Houkyaku_Start")
	{
		GC(cAnimation)->SetAnimation("Houkyaku_Charge");
		AddHitBox(Vec2(40, 30), Vec2(20, 0), 10, 0, 0, Vec2(0, 0), 35, 1, 0, 0, "Houkyaku_Charge");
		AddForce(m_SubState == State_Air ? 700 : 1000, 0);
		return;
	}

	if (_Key == "Houkyaku")
	{
		GC(cAnimation)->SetAnimation("Houkyaku_End");
		m_MainState = State_Attack;
		return;
	}
}

void cKim::OnAnimationNotify(string _Key)
{
	cPlayer::OnAnimationNotify(_Key);

	if (_Key == "WPunch_Attack1")
	{
		AddHitBox(Vec2(20, 10), Vec2(30, -25), 0.05, 10 * m_Damage, 5 * m_Damage, Vec2(75, 0), 20, 0.3, 0.05, 2);
		m_CancelAble = true;
		m_Owner->SetAlarm(4, 0.13);
		return;
	}
	if (_Key == "WKick_Attack1")
	{
		AddHitBox(Vec2(35, 10), Vec2(40, -30), 0.1, 15 * m_Damage, 7 * m_Damage, Vec2(100, 0), 25, 0.4, 0.05, 2);
		m_CancelAble = true;
		m_Owner->SetAlarm(4, 0.1);
		return;
	}
	if (_Key == "SPunch_Attack1")
	{
		AddHitBox(Vec2(30, 20), Vec2(30, 0), 0.05, 10 * m_Damage, 6 * m_Damage, Vec2(0, 0), 30, 0.6, 0.08, 3);
		return;
	}
	if (_Key == "SPunch_Attack2")
	{
		AddHitBox(Vec2(30, 20), Vec2(30, 0), 0.05, 10 * m_Damage, 6 * m_Damage, Vec2(200, 0), 30, 0.65, 0.08, 3);
		m_CancelAble = true;
		m_Owner->SetAlarm(4, 0.15);
		return;
	}
	if (_Key == "SKick_Attack1")
	{
		AddHitBox(Vec2(20, 30), Vec2(45, -50), 0.2, 30 * m_Damage, 15 * m_Damage, Vec2(100, -600), 40, 0.75, 0.15, 4);
		m_CancelAble = true;
		m_Owner->SetAlarm(4, 0.15);
		return;
	}

	if (_Key == "WPunch_Air_Attack1")
	{
		AddHitBox(Vec2(15, 15), Vec2(5, 25), 0.1, 10 * m_Damage, 10 * m_Damage, Vec2(50, 0), 20, 0.4, 0.1, 2);
		return;
	}
	if (_Key == "WKick_Air_Attack1")
	{
		AddHitBox(Vec2(20, 30), Vec2(25, -5), 0.15, 15 * m_Damage, 15 * m_Damage, Vec2(75, 0), 25, 0.6, 0.1, 2);
		return;
	}
	if (_Key == "SKick_Air_Attack1")
	{
		AddHitBox(Vec2(30, 30), Vec2(40, 0), 0.2, 50 * m_Damage, 50 * m_Damage, Vec2(100, 1000), 30, 0.6, 0.15, 4);
		return;
	}
	if (_Key == "SPunch_Air_Attack1")
	{
		AddHitBox(Vec2(35, 15), Vec2(35, 20), 0.25, 30 * m_Damage, 30 * m_Damage, Vec2(150, 750), 40, 0.8, 0.2, 5);
		return;
	}

	if (_Key == "Hangetsuzan_Force1")
	{
		AddForce(300, -250);
		return;
	}
	if (_Key == "Hangetsuzan_Attack1")
	{
		AddHitBox(Vec2(45, 45), Vec2(50, 5), 0.1, 15 * m_Damage, 12 * m_Damage, Vec2(100, 0), 30, 0.5, 0.1, 6);
		SOUND->Play("Kim_Hangetsuzan_Effect", -500);
		return;
	}
	if (_Key == "Hangetsuzan_Attack2")
	{
		AddHitBox(Vec2(45, 35), Vec2(50, 15), 0.1, 25 * m_Damage, 20 * m_Damage, Vec2(175, -500), 30, 0.9, 0.15, 6);
		GC(cAnimation)->m_Speed - 0.5f;
		return;
	}

	if (_Key == "Hangetsuzan_Air_Force1")
	{
		AddForce(150, -200);
		return;
	}
	if (_Key == "Hangetsuzan_Air_Attack1")
	{
		AddHitBox(Vec2(45, 50), Vec2(50, 0), 0.1, 25 * m_Damage, 25 * m_Damage, Vec2(50, 0), 30, 0.5, 0.1, 6);
		SOUND->Play("Kim_Hangetsuzan_Effect", -500);
		return;
	}
	if (_Key == "Hangetsuzan_Air_Attack2")
	{
		AddHitBox(Vec2(45, 50), Vec2(50, 0), 0.1, 30 * m_Damage, 30 * m_Damage, Vec2(150, 1000), 30, 0.5, 0.15, 8);
		return;
	}

	if (_Key == "Hienzan_Force1")
	{
		AddForce(200, -800);
		return;
	}
	if (_Key == "Hienzan_Attack1")
	{
		AddHitBox(Vec2(30, 40), Vec2(40, 0), 0.1, 20 * m_Damage, 10 * m_Damage, Vec2(100, -350), 40, 0.5, 0.15, 6, "", true, 3);
		return;
	}
	if (_Key == "Hienzan_Attack2")
	{
		AddHitBox(Vec2(50, 50), Vec2(50, 0), 0.1, 20 * m_Damage, 20 * m_Damage, Vec2(200, -550), 40, 0.5, 0.2, 10, "", true, 3);
		return;
	}

	if (_Key == "Hisyokyaku_Attack1")
	{
		AddHitBox(Vec2(40, 40), Vec2(30, 30), 0.05, 20 * m_Damage, 10 * m_Damage, Vec2(200, 0), 25, 0.55, 0.05, 5, "Hisyokyaku");
		return;
	}

	if (_Key == "Sanengeki1_Force1")
	{
		AddForce(250, 0);
		return;
	}
	if (_Key == "Sanengeki1_Attack1")
	{
		AddHitBox(Vec2(30, 30), Vec2(40, -40), 0.1, 20 * m_Damage, 20 * m_Damage, Vec2(175, 0), 20, 0.8, 0.1, 6);
		m_SanengekiPhase = 2;
		return;
	}
	if (_Key == "Sanengeki1_Cancel1")
	{
		if (m_SanengekiPhase == 3)
		{
			m_SanengekiPhase = 4;
			GC(cAnimation)->SetAnimation("Sanengeki2");
			PlayVoice("Kim_Attack3");
			AddForce(250, 0);
		}
		return;
	}

	if (_Key == "Sanengeki2_Attack1")
	{
		AddHitBox(Vec2(30, 20), Vec2(40, -30), 0.1, 20 * m_Damage, 20 * m_Damage, Vec2(300, -500), 20, 0.8, 0.1, 6);
		m_SanengekiPhase = 5;
		return;
	}

	if (_Key == "Sanengeki2_Cancel1")
	{
		if (m_SanengekiPhase == 6)
		{
			m_SanengekiPhase = 7;
			GC(cAnimation)->SetAnimation("Sanengeki3");
			PlayVoice("Kim_Attack4");
			AddForce(250, -450);
		}
		return;
	}

	if (_Key == "Sanengeki3_Attack1")
	{
		AddHitBox(Vec2(45, 30), Vec2(50, -30), 0.1, 30 * m_Damage, 30 * m_Damage, Vec2(200, -250), 20, 0.8, 0.1, 8, "", true, 3);
		return;
	}
	if (_Key == "Sanengeki3_Attack2")
	{
		AddHitBox(Vec2(45, 30), Vec2(50, -30), 0.1, 30 * m_Damage, 30 * m_Damage, Vec2(250, -350), 20, 0.8, 0.2, 10, "", true, 3);
		return;
	}

	if (_Key == "GuardCancel_Attack1")
	{
		AddHitBox(Vec2(40, 20), Vec2(45, -25), 0.15, 50 * m_Damage, 0 * m_Damage, Vec2(50, -800), 40, 0.75, 0.2, 6, "GuardCancel");
		AddForce(75, 0);
		return;
	}

	if (_Key == "Houkyaku_Start1")
	{
		PlayVoice("Kim_Kyaku");
		GC(cAnimation)->m_Speed = 0.8;
		return;
	}
	if (_Key == "Houkyaku_Attack1")
	{
		AddHitBox(Vec2(40, 30), Vec2(45, 0), 0.05, 11 * m_Damage, 0 * m_Damage, Vec2(85, 0), 35, 0.4, 0, 5, "Flash", true, 2);
		return;
	}
	if (_Key == "Houkyaku_Force1")
	{
		AddForce(400, -400);
		return;
	}
	if (_Key == "Houkyaku_Attack2")
	{
		AddHitBox(Vec2(50, 40), Vec2(50, 0), 0.05, 16 * m_Damage, 0 * m_Damage, Vec2(290, -400), 35, 0.4, 0, 5, "Flash", true, 3);
		return;
	}
	if (_Key == "Houkyaku_Attack3")
	{
		AddHitBox(Vec2(50, 40), Vec2(50, 0), 0.05, 60 * m_Damage, 0 * m_Damage, Vec2(300, 1500), 35, 0.4, 0.6, 15, "", true, 3);
		GC(cAnimation)->m_Speed = 0.4f;
		return;
	}
}

void cKim::OnHit(string _Key, cObject * _Other, RECT _Rect)
{
	cPlayer::OnHit(_Key, _Other, _Rect);
	if (_Key == "Hisyokyaku")
	{
		if (_Other->GC(cCharacter)->m_SubState == State_Air)
		{
			_Other->GC(cCharacter)->AddForce(-175, -30);
		}
	}

	if (_Key == "GuardCancel")
	{
		_Other->GC(cCharacter)->m_SuperArmor = false;
		return;
	}

	if (_Key == "Houkyaku_Charge" && m_HitBox != nullptr)
	{
		GC(cAnimation)->SetAnimation("Houkyaku");
		PlayVoice("Kim_Ata_Start");
		m_Owner->SetAlarm(6, 0.8);
		m_HitBox->m_Owner->m_Destroyed = true;
		m_HitBox = nullptr;
		m_Velocity.x = 0;
		_Other->m_Pos.x = m_Owner->m_Pos.x + 50 * m_Owner->m_Scale.x;
		if (_Other->GC(cCharacter)->m_SubState == State_Air)
		{
			_Other->GC(cCharacter)->m_SubState = State_Ground;
			_Other->GC(cCharacter)->m_Ground = nullptr;
			_Other->GC(cCharacter)->m_Velocity = Vec2(0, 500);
			_Other->m_Pos.y = m_Owner->m_Pos.y - 10;
		}
		return;
	}
}

void cKim::Death()
{
	cPlayer::Death();
	m_Owner->SetAlarm(7, SYSTEM->m_GameMode == GM_PvE ? 20 : 3);
}