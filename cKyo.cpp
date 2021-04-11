#include "DXUT.h"
#include "cKyo.h"
#include "cEnemy.h"


cKyo::cKyo()
{
}


cKyo::~cKyo()
{
}

void cKyo::Init()
{
	cPlayer::Init();
	GC(cCollider)->Setting(Vec2(30, 50), Vec2(0, 0));
	GC(cRenderer)->m_ShadowOffset = -25;

	GC(cAnimation)->AddAnimation("Idle", m_Owner->m_Name + "_Idle", 0.1);
	GC(cAnimation)->AddAnimation("Walk", m_Owner->m_Name + "_Walk", 0.15);
	GC(cAnimation)->AddAnimation("Run", m_Owner->m_Name + "_Run", 0.09);
	GC(cAnimation)->AddAnimation("Wake", m_Owner->m_Name + "_Wake", 0.07);
	GC(cAnimation)->AddAnimation("Dodge", m_Owner->m_Name + "_Dodge", 0.09);

	GC(cAnimation)->AddAnimation("WPunch", m_Owner->m_Name + "_WPunch", 0.07);
	GC(cAnimation)->AddNotify("WPunch", 2, "WPunch_Attack1");
	GC(cAnimation)->AddAnimation("WKick", m_Owner->m_Name + "_WKick", 0.05);
	GC(cAnimation)->AddNotify("WKick", 4, "WKick_Attack1");
	GC(cAnimation)->AddAnimation("SPunch", m_Owner->m_Name + "_SPunch", 0.09);
	GC(cAnimation)->AddNotify("SPunch", 3, "SPunch_Attack1");
	GC(cAnimation)->AddAnimation("SKick", m_Owner->m_Name + "_SKick", 0.08);
	GC(cAnimation)->AddNotify("SKick", 6, "SKick_Attack1");

	GC(cAnimation)->AddAnimation("WPunch_Air", m_Owner->m_Name + "_WPunch_Air", 0.07);
	GC(cAnimation)->AddNotify("WPunch_Air", 3, "WPunch_Air_Attack1");
	GC(cAnimation)->AddAnimation("WKick_Air", m_Owner->m_Name + "_WKick_Air", 0.08);
	GC(cAnimation)->AddNotify("WKick_Air", 3, "WKick_Air_Attack1");
	GC(cAnimation)->AddAnimation("SPunch_Air", m_Owner->m_Name + "_SPunch_Air", 0.05);
	GC(cAnimation)->AddNotify("SPunch_Air", 5, "SPunch_Air_Attack1");
	GC(cAnimation)->AddAnimation("SKick_Air", m_Owner->m_Name + "_SKick_Air", 0.1);
	GC(cAnimation)->AddNotify("SKick_Air", 4, "SKick_Air_Attack1");

	GC(cAnimation)->AddAnimation("GuardCancel", m_Owner->m_Name + "_GuardCancel", 0.05);
	GC(cAnimation)->AddNotify("GuardCancel", 6, "GuardCancel_Attack1");

	GC(cAnimation)->AddAnimation("Aragami1", m_Owner->m_Name + "_Aragami1_", 0.04);
	GC(cAnimation)->AddNotify("Aragami1", 4, "Aragami1_Force1");
	GC(cAnimation)->AddNotify("Aragami1", 8, "Aragami1_Attack1");
	GC(cAnimation)->AddNotify("Aragami1", 12, "Aragami1_Next");

	GC(cAnimation)->AddAnimation("Aragami2", m_Owner->m_Name + "_Aragami2_", 0.07);
	GC(cAnimation)->AddNotify("Aragami2", 4, "Aragami2_Force1");
	GC(cAnimation)->AddNotify("Aragami2", 5, "Aragami2_Attack1");
	GC(cAnimation)->AddNotify("Aragami2", 7, "Aragami2_Next");

	GC(cAnimation)->AddAnimation("Aragami3", m_Owner->m_Name + "_Aragami3_", 0.08);
	GC(cAnimation)->AddNotify("Aragami3", 6, "Aragami3_Attack1");
	GC(cAnimation)->AddNotify("Aragami3", 10, "Aragami3_Attack2");
	GC(cAnimation)->AddNotify("Aragami3", 11, "Aragami3_Attack3");
	GC(cAnimation)->AddNotify("Aragami3", 12, "Aragami3_Attack4");

	GC(cAnimation)->AddAnimation("Aragami_Air", m_Owner->m_Name + "_Aragami_Air", 0.08);
	GC(cAnimation)->AddNotify("Aragami_Air", 3, "Aragami_Air_Attack1");
	GC(cAnimation)->AddNotify("Aragami_Air", 12, "Aragami_Air_Attack2");

	GC(cAnimation)->AddAnimation("Kai", m_Owner->m_Name + "_Kai", 0.11);
	GC(cAnimation)->AddNotify("Kai", 5, "Kai_Attack1");
	GC(cAnimation)->AddNotify("Kai", 8, "Kai_Attack2");

	GC(cAnimation)->AddAnimation("Oniyaki", m_Owner->m_Name + "_Oniyaki", 0.09);
	GC(cAnimation)->AddNotify("Oniyaki", 2, "Oniyaki_Attack1");
	GC(cAnimation)->AddNotify("Oniyaki", 3, "Oniyaki_Attack2");
	GC(cAnimation)->AddNotify("Oniyaki", 4, "Oniyaki_Attack3");

	GC(cAnimation)->AddAnimation("Charge_Start", m_Owner->m_Name + "_182_Start", 0.04);
	GC(cAnimation)->AddAnimation("Charge", m_Owner->m_Name + "_182_Charge", 0.05);

	GC(cAnimation)->AddAnimation("182_End", m_Owner->m_Name + "_182_End", 0.06);
	GC(cAnimation)->AddNotify("182_End", 9, "182_Attack1");

	GC(cAnimation)->AddAnimation("Red", m_Owner->m_Name + "_RedKick", 0.07);
	GC(cAnimation)->AddNotify("Red", 3, "Red_Force1");
	GC(cAnimation)->AddNotify("Red", 8, "Red_Attack1");

	GC(cAnimation)->AddAnimation("Mushiki1", m_Owner->m_Name + "_Mushiki_Start", 0.04);
	GC(cAnimation)->AddNotify("Mushiki1", 14, "Mushiki1_Attack1");

	GC(cAnimation)->AddAnimation("Mushiki2", m_Owner->m_Name + "_Mushiki_1_", 0.01);
	GC(cAnimation)->AddNotify("Mushiki2", 10, "Mushiki2_Attack1");

	GC(cAnimation)->AddAnimation("Mushiki3", m_Owner->m_Name + "_Mushiki_2_", 0.02);
	GC(cAnimation)->AddNotify("Mushiki3", 4, "Mushiki3_Attack1");

	GC(cAnimation)->AddAnimation("Mushiki4", m_Owner->m_Name + "_Mushiki_3_", 0.02);
	GC(cAnimation)->AddNotify("Mushiki4", 4, "Mushiki4_Attack1");

	GC(cAnimation)->AddAnimation("Mushiki5", m_Owner->m_Name + "_Mushiki_4_", 0.09);
	GC(cAnimation)->AddNotify("Mushiki5", 1, "Mushiki5_Attack1");
	GC(cAnimation)->AddNotify("Mushiki5", 5, "Mushiki5_Effect1");

	GC(cAnimation)->SetAnimation("Idle");
	m_MaxHp = SYSTEM->m_PlayerRemain == 1 ? 1500 : 750;
	m_Hp = m_MaxHp;
	m_MaxStun = 100000;
	m_Stun = 100000;
	m_182Charge = 0;
	m_RedCharge = 0;
	m_182Charging = false;
	m_RedCharging = false;
	m_AragamiPhase = 0;
	m_HitSound = 2;
	m_Shift = false;
	m_CancelAble = false;
	m_Killed = 0;
	m_Dealt = 0;
	m_Damage = 1;

	m_Owner->SetAlarmSize(7);
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
		}
	};
}

void cKyo::Update()
{
	if (GC(cAnimation)->m_CurAnim->Key == "Aragami_Air")
	{
		m_Owner->m_Pos.y -= m_Velocity.y * DT;
		m_Velocity.y = 0;
	}
	cPlayer::Update();

	if ((m_MainState == State_Idle || m_MainState == State_Walk || m_MainState == State_Run) || (m_CancelAble && m_MainState != State_Skill))
	{
		if (m_GaugeStock != 0)
		{
			if (INPUT->CheckCommand(Cmd_2626, Key_WPunch, m_Side) || INPUT->CheckCommand(Cmd_2626, Key_SPunch, m_Side))
			{
				if (m_SubState == State_Ground)
				{
					m_GaugeStock--;
					GC(cAnimation)->SetAnimation("Mushiki1");
					PlayVoice("Kyo_Mushiki");
					cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
					Anim->m_Anim = IMAGE->FindAnimation("Flash");
					Anim->m_Speed = 0.035;
					SOUND->Play("Flash", 0);
					m_MainState = State_Skill;
				}
			}
		}

		if (INPUT->CheckCommand(Cmd_626, Key_WPunch, m_Side) || INPUT->CheckCommand(Cmd_626, Key_SPunch, m_Side))
		{
			if (m_SubState == State_Ground)
			{
				GC(cAnimation)->SetAnimation("Oniyaki");
				GC(cAnimation)->m_Speed = 0.3;
				PlayVoice("Kyo_Oniyaki");
				m_MainState = State_Skill;
				m_GuardPoint = true;
				m_Owner->SetAlarm(5, 0.3);
				AddForce(50, 0);
			}
		}

		if (INPUT->CheckCommand(Cmd_26, Key_WPunch, m_Side) || INPUT->CheckCommand(Cmd_26, Key_SPunch, m_Side))
		{
			if (m_SubState == State_Ground)
			{
				GC(cAnimation)->SetAnimation("Aragami1");
				m_AragamiPhase = 1;
				PlayVoice("Kyo_Aragami1");
				m_MainState = State_Skill;
			}
		}

		if (INPUT->CheckCommand(Cmd_22, Key_WPunch, m_Side) || INPUT->CheckCommand(Cmd_22, Key_SPunch, m_Side))
		{
			if (m_SubState == State_Air)
			{
				GC(cAnimation)->SetAnimation("Aragami_Air");
				PlayVoice("Kyo_Aragami_Air");
				m_MainState = State_Skill;
				m_Velocity.x = 0;
			}
		}

		if (INPUT->CheckCommand(Cmd_26, Key_WKick, m_Side) || INPUT->CheckCommand(Cmd_26, Key_SKick, m_Side))
		{
			if (m_SubState == State_Ground)
			{
				GC(cAnimation)->SetAnimation("Kai");
				m_MainState = State_Skill;
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
				PlayVoice(RandomText("Kyo_Attack", 1, 2));
			}
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_WKick]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("WKick");
				PlayVoice(RandomText("Kyo_Attack", 1, 2));
			}
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_SPunch]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("SPunch");
				PlayVoice(RandomText("Kyo_Attack", 3, 4));
			}
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_SKick]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("SKick");
				PlayVoice(RandomText("Kyo_Attack", 3, 4));
			}

			if (INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_WPunch]) && INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_WKick]))
			{
				GC(cAnimation)->SetAnimation("Dodge");
				AddForce(500, 0);
				PlayVoice("Kyo_Dodge");
				m_MainState = State_Dodge;
			}
		}
		else
		{
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_WPunch]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("WPunch_Air");
				PlayVoice(RandomText("Kyo_Attack", 1, 2));
			}
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_WKick]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("WKick_Air");
				PlayVoice(RandomText("Kyo_Attack", 1, 2));
			}
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_SPunch]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("SPunch_Air");
				PlayVoice(RandomText("Kyo_Attack", 3, 4));
			}
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_SKick]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("SKick_Air");
				PlayVoice(RandomText("Kyo_Attack", 3, 4));
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
			PlayVoice("Kyo_GuardCancel");
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

	if (m_AragamiPhase != 0)
	{
		if (m_AragamiPhase == 2 && INPUT->CheckCommand(Cmd_624, Key_WPunch, m_Side) || INPUT->CheckCommand(Cmd_624, Key_SPunch, m_Side))
		{
			m_AragamiPhase = 3;
		}
		else if (m_AragamiPhase == 5 && INPUT->CheckCommand(Cmd_26, Key_WPunch, m_Side) || INPUT->CheckCommand(Cmd_26, Key_SPunch, m_Side))
		{
			m_AragamiPhase = 6;
		}
	}

	if (m_MainState == State_Skill)
	{
		if (m_182Charging)
		{
			m_182Charge += 0.5 * DT;
			if (m_182Charge >= 2 || (!INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_WPunch]) && !INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_SPunch])))
			{
				m_182Charging = false;
				GC(cAnimation)->SetAnimation("182_End");
				PlayVoice("Kyo_182_End");
			}
		}
		if (m_RedCharging)
		{
			m_RedCharge += 0.5 * DT;
			if (m_RedCharge >= 2 || (!INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_WKick]) && !INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_SKick])))
			{
				m_RedCharging = false;
				GC(cAnimation)->SetAnimation("Red");
				PlayVoice("Kyo_Red");
			}
		}
	}
	else
	{
		m_182Charge = 0;
		m_182Charging = false;
		m_RedCharge = 0;
		m_RedCharging = false;
		m_GuardPointHited = false;
	}

	if (!m_Dead)
		m_Owner->m_Pos.x = Clamp(m_Owner->m_Pos.x, CAMERA->m_Pos.x - 480, CAMERA->m_Pos.x + 480);
}

void cKyo::Render()
{
	cPlayer::Render();
}

void cKyo::Release()
{
	cCharacter::Release();
	SYSTEM->m_Player[m_Side] = nullptr;
	if (m_Dead == false)
		SYSTEM->m_PlayerRemain--;
}

void cKyo::OnCollision(cObject * _Other, RECT _Rect)
{
	cPlayer::OnCollision(_Other, _Rect);
}

void cKyo::OnAnimationEnd(string _Key)
{
	cPlayer::OnAnimationEnd(_Key);

	if (_Key == "WPunch" || _Key == "WKick" || _Key == "SPunch" || _Key == "SKick" || _Key == "WPunch_Air" || _Key == "WKick_Air" || _Key == "SPunch_Air" || _Key == "SKick_Air" ||
		_Key == "Aragami1" || _Key == "Aragami2"|| _Key == "Oniyaki" || _Key == "182_End" || _Key == "Red" || _Key == "Dodge" || _Key == "GuardCancel"||
		_Key == "Aragami_Air" || _Key == "Mushiki5")
	{
		Idle();
		return;
	}

	if (_Key == "Aragami3")
	{
		if (INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_WPunch]) || INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_SPunch]))
		{
			m_182Charge = 1;
			GC(cAnimation)->SetAnimation("Charge_Start");
			PlayVoice("Kyo_182_Charge");
		}
		else
		{
			Idle();
		}
		return;
	}

	if (_Key == "Kai")
	{
		if (INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_WKick]) || INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_SKick]))
		{
			m_RedCharge = 1;
			GC(cAnimation)->SetAnimation("Charge_Start");
			PlayVoice("Kyo_182_Charge");
		}
		else
		{
			Idle();
		}
		return;
	}

	if (_Key == "Charge_Start")
	{
		GC(cAnimation)->SetAnimation("Charge");
		if (m_182Charge == 1)
		{
			m_182Charging = true;
		}
		if (m_RedCharge == 1)
		{
			m_RedCharging = true;
		}
		return;
	}

	if (_Key == "Mushiki1")
	{
		GC(cAnimation)->SetAnimation("Mushiki2");
		m_MushikiLoop = 2;
		m_MushikiPos = m_Owner->m_Pos;
		AddForce(550, 0);
		SOUND->Play("Swing2", -500);
		return;
	}

	if (_Key == "Mushiki2")
	{
		if (m_MushikiLoop != 0)
		{
			m_MushikiLoop--;
			m_Owner->m_Pos = m_MushikiPos;
			AddForce(550, 0);
			SOUND->Play("Swing2", -500);
		}
		else
		{
			GC(cAnimation)->SetAnimation("Mushiki3");
			m_MushikiLoop = 2;
			m_MushikiPos = m_Owner->m_Pos;
			AddForce(300, 0);
			SOUND->Play("Swing6", -500);
		}
		return;
	}

	if (_Key == "Mushiki3")
	{
		if (m_MushikiLoop != 0)
		{
			m_MushikiLoop--;
			m_Owner->m_Pos = m_MushikiPos;
			AddForce(300, 0);
			SOUND->Play("Swing6", -500);
		}
		else
		{
			GC(cAnimation)->SetAnimation("Mushiki4");
			m_MushikiLoop = 2;
			m_MushikiPos = m_Owner->m_Pos;
			AddForce(150, -350);
			SOUND->Play("Swing1", -500);
		}
		return;
	}

	if (_Key == "Mushiki4")
	{
		if (m_MushikiLoop != 0)
		{
			m_MushikiLoop--;
			m_Owner->m_Pos = m_MushikiPos;
			AddForce(150, -350);
			SOUND->Play("Swing1", -500);
		}
		else
		{
			GC(cAnimation)->SetAnimation("Mushiki5");
			AddForce(50, -600);
		}
		return;
	}
}

void cKyo::OnAnimationNotify(string _Key)
{
	cPlayer::OnAnimationNotify(_Key);

	if (_Key == "WPunch_Attack1")
	{
		AddHitBox(Vec2(15, 10), Vec2(25, -25), 0.05, 10 * m_Damage, 5 * m_Damage, Vec2(75, 0), 20, 0.3, 0.05, 2);
		m_CancelAble = true;
		m_Owner->SetAlarm(4, 0.1);
		return;
	}
	if (_Key == "WKick_Attack1")
	{
		AddHitBox(Vec2(35, 10), Vec2(45, -20), 0.1, 15 * m_Damage, 7 * m_Damage, Vec2(100, 0), 25, 0.4, 0.05, 2);
		m_CancelAble = true;
		m_Owner->SetAlarm(4, 0.1);
		return;
	}
	if (_Key == "SPunch_Attack1")
	{
		AddHitBox(Vec2(20, 30), Vec2(30, -40), 0.05, 30 * m_Damage, 15 * m_Damage, Vec2(150, 0), 30, 0.6, 0.1, 3);
		m_CancelAble = true;
		m_Owner->SetAlarm(4, 0.12);
		return;
	}
	if (_Key == "SKick_Attack1")
	{
		AddHitBox(Vec2(35, 15), Vec2(35, -5), 0.2, 45 * m_Damage, 25 * m_Damage, Vec2(225, 0), 40, 0.75, 0.15, 4);
		m_CancelAble = true;
		m_Owner->SetAlarm(4, 0.2);
		AddForce(100, 0);
		return;
	}

	if (_Key == "WPunch_Air_Attack1")
	{
		AddHitBox(Vec2(15, 15), Vec2(30, 20), 0.1, 10 * m_Damage, 10 * m_Damage, Vec2(50, 0), 20, 0.4, 0.1, 2);
		return;
	}
	if (_Key == "WKick_Air_Attack1")
	{
		AddHitBox(Vec2(15, 15), Vec2(20, 25), 0.15, 20 * m_Damage, 20 * m_Damage, Vec2(75, 0), 25, 0.6, 0.1, 2);
		return;
	}
	if (_Key == "SPunch_Air_Attack1")
	{
		AddHitBox(Vec2(20, 20), Vec2(30, 30), 0.2, 30 * m_Damage, 30 * m_Damage, Vec2(100, 750), 30, 0.6, 0.2, 4);
		return;
	}
	if (_Key == "SKick_Air_Attack1")
	{
		AddHitBox(Vec2(35, 15), Vec2(35, 5), 0.25, 45 * m_Damage, 45 * m_Damage, Vec2(150, 750), 40, 0.8, 0.2, 5);
		return;
	}

	if (_Key == "Aragami1_Force1")
	{
		m_AragamiPhase = 2;
		AddForce(300, 0);
		m_GuardPoint = true;
		m_Owner->SetAlarm(5, 0.15);
		return;
	}
	if (_Key == "Aragami1_Attack1")
	{
		if(m_GuardPointHited == false)
			AddHitBox(Vec2(25, 20), Vec2(25, 0), 0.1, 45 * m_Damage, 30 * m_Damage, Vec2(350, 0), 35, 0.7, 0.15, 4, "Fire");
		else
			AddHitBox(Vec2(25, 20), Vec2(25, 0), 0.1, 90 * m_Damage, 60 * m_Damage, Vec2(350, 0), 35, 0.7, 0.25, 5, "Fire");
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, m_Owner->m_Scale, 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Kyo_Aragami_Fire1_");
		Anim->m_Speed = 0.05;
		return;
	}
	if (_Key == "Aragami1_Next")
	{
		GC(cAnimation)->m_Speed = 0.8f;
		if (m_AragamiPhase == 3)
		{
			m_AragamiPhase = 4;
			GC(cAnimation)->SetAnimation("Aragami2");
			PlayVoice("Kyo_Aragami2");
		}
		return;
	}

	if (_Key == "Aragami2_Force1")
	{
		m_AragamiPhase = 5;
		AddForce(350, 0);
		return;
	}
	if (_Key == "Aragami2_Attack1")
	{
		if (m_GuardPointHited == false)
			AddHitBox(Vec2(25, 30), Vec2(25, -30), 0.1, 40 * m_Damage, 30 * m_Damage, Vec2(100, -650), 35, 0.75, 0.15, 4, "Fire");
		else
			AddHitBox(Vec2(25, 30), Vec2(25, -30), 0.1, 80 * m_Damage, 60 * m_Damage, Vec2(100, -650), 35, 0.75, 0.25, 5, "Fire");
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, m_Owner->m_Scale, 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Kyo_Aragami_Fire2_");
		Anim->m_Speed = 0.05;
		return;
	}
	if (_Key == "Aragami2_Next")
	{
		if (m_AragamiPhase == 6)
		{
			m_AragamiPhase = 7;
			GC(cAnimation)->SetAnimation("Aragami3");
		}
		return;
	}

	if (_Key == "Aragami3_Attack1")
	{
		AddForce(100, -500);
		if (m_GuardPointHited == false)
			AddHitBox(Vec2(30, 40), Vec2(30, -40), 0.1, 25 * m_Damage, 15 * m_Damage, Vec2(50, -500), 35, 0.75, 0.15, 4);
		else
			AddHitBox(Vec2(30, 40), Vec2(30, -40), 0.1, 50 * m_Damage, 30 * m_Damage, Vec2(50, -500), 35, 0.75, 0.25, 5);
		return;
	}
	if (_Key == "Aragami3_Attack2")
	{
		GC(cAnimation)->m_Speed = 1;
		AddForce(50, -700);
		if (m_GuardPointHited == false)
			AddHitBox(Vec2(20, 40), Vec2(40, -30), 0.05, 15 * m_Damage, 10 * m_Damage, Vec2(50, -400), 40, 1, 0.12, 5, "Fire");
		else	
			AddHitBox(Vec2(20, 40), Vec2(40, -30), 0.05, 30 * m_Damage, 20 * m_Damage, Vec2(50, -400), 40, 1, 0.2, 6, "Fire");
		PlayVoice("Kyo_Aragami3");
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos - Vec2(0, 50), m_Owner->m_Scale, 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Kyo_Oniyaki_Fire1");
		Anim->m_Speed = 0.05;
		return;
	}
	if (_Key == "Aragami3_Attack3")
	{
		if (m_GuardPointHited == false)
			AddHitBox(Vec2(20, 40), Vec2(40, -30), 0.05, 15 * m_Damage, 10 * m_Damage, Vec2(100, -500), 40, 1, 0.12, 4, "Fire");
		else
			AddHitBox(Vec2(20, 40), Vec2(40, -30), 0.05, 30 * m_Damage, 20 * m_Damage, Vec2(100, -500), 40, 1, 0.2, 5, "Fire");
		return;
	}
	if (_Key == "Aragami3_Attack4")
	{
		if (m_GuardPointHited == false)
			AddHitBox(Vec2(20, 40), Vec2(40, -30), 0.05, 15 * m_Damage, 10 * m_Damage, Vec2(100, -700), 40, 1, 0.12, 3, "Fire");
		else
			AddHitBox(Vec2(20, 40), Vec2(40, -30), 0.05, 30 * m_Damage, 20 * m_Damage, Vec2(100, -700), 40, 1, 0.2, 4, "Fire");
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos - Vec2(0,40), m_Owner->m_Scale, 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Kyo_Oniyaki_Fire2");
		Anim->m_Speed = 0.05;
		return;
	}

	if (_Key == "Kai_Attack1")
	{
		AddForce(75, -450);
		AddHitBox(Vec2(20, 30), Vec2(30, -40), 0.1, 20 * m_Damage, 10 * m_Damage, Vec2(50, -500), 25, 0.75, 0.1, 3);
		PlayVoice("Kyo_Attack2");
		return;
	}
	if (_Key == "Kai_Attack2")
	{
		AddForce(75, -450);
		AddHitBox(Vec2(20, 30), Vec2(40, -40), 0.1, 20 * m_Damage, 10 * m_Damage, Vec2(100, -600), 25, 0.75, 0.1, 3);
		PlayVoice("Kyo_Attack2");
		return;
	}

	if (_Key == "Oniyaki_Attack1")
	{
		GC(cAnimation)->m_Speed = 1;
		AddForce(10, -800);
		if (m_GuardPointHited == false)
			AddHitBox(Vec2(20, 40), Vec2(40, -30), 0.05, 40 * m_Damage, 30 * m_Damage, Vec2(75, -500), 40, 1, 0.12, 5, "Fire");
		else
			AddHitBox(Vec2(20, 40), Vec2(40, -30), 0.05, 80 * m_Damage, 60 * m_Damage, Vec2(75, -500), 40, 1, 0.3, 7, "Fire");
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos - Vec2(0, 50), m_Owner->m_Scale, 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Kyo_Oniyaki_Fire1");
		Anim->m_Speed = 0.05;
		return;
	}
	if (_Key == "Oniyaki_Attack2")
	{
		if (m_GuardPointHited == false)
			AddHitBox(Vec2(20, 40), Vec2(40, -30), 0.05, 30 * m_Damage, 20 * m_Damage, Vec2(75, -600), 40, 1, 0.12, 4, "Fire");
		else
			AddHitBox(Vec2(20, 40), Vec2(40, -30), 0.05, 60 * m_Damage, 40 * m_Damage, Vec2(75, -600), 40, 1, 0.2, 6, "Fire");
		return;
	}
	if (_Key == "Oniyaki_Attack3")
	{
		if (m_GuardPointHited == false)
			AddHitBox(Vec2(20, 40), Vec2(40, -30), 0.05, 20 * m_Damage, 20 * m_Damage, Vec2(90, -700), 40, 1, 0.12, 3, "Fire");
		else
			AddHitBox(Vec2(20, 40), Vec2(40, -30), 0.05, 40 * m_Damage, 40 * m_Damage, Vec2(90, -700), 40, 1, 0.2, 5, "Fire");
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos - Vec2(0, 40), m_Owner->m_Scale, 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Kyo_Oniyaki_Fire2");
		Anim->m_Speed = 0.05;
		return;
	}

	if (_Key == "GuardCancel_Attack1")
	{
		AddHitBox(Vec2(40, 40), Vec2(40, 0), 0.15, 50 * m_Damage, 0 * m_Damage, Vec2(50, -800), 40, 0.75, 0.2, 6, "GuardCancel");
		AddForce(75, 0);
		return;
	}

	if (_Key == "182_Attack1")
	{
		AddForce(150, 0);
		AddHitBox(Vec2(40, 50), Vec2(0, 0), 100, 100 * m_Damage * m_182Charge, 50 * m_Damage * m_182Charge, Vec2(100, -750), 35, 2, 0.2, 6, "182_Hit");
		cObject* a = FireMissile("Kyo_182_Fire", 0.1, m_Owner->m_Pos, 500, m_Owner->m_Scale.x == 1 ? 0 : 180)->m_Owner;
		a->SetAlarm(0, 1.2);
		a->m_Tag = Obj_Player;
		SOUND->Play("Kyo_182_End_Effect", -500);
		return;
	}

	if (_Key == "Red_Force1")
	{
		AddForce(250, -600);
		SOUND->Play("Kyo_Red_Effect", -500);
		return;
	}
	if (_Key == "Red_Attack1")
	{
		AddHitBox(Vec2(40, 30), Vec2(30, 10), 0.15, 50 * m_Damage * m_RedCharge, 100 * m_Damage * m_RedCharge, Vec2(100, 1500), 30, 1, 0.5, 7);
		return;
	}

	if (_Key == "Aragami_Air_Attack1")
	{
		AddHitBox(Vec2(35, 10), Vec2(35, 10), 0.1, 30 * m_Damage, 35 * m_Damage, Vec2(0, -700), 30, 1, 0.15, 5);
		return;
	}
	if (_Key == "Aragami_Air_Attack2")
	{
		AddHitBox(Vec2(25, 25), Vec2(25, 15), 0.2, 60 * m_Damage, 90 * m_Damage, Vec2(0, 1500), 30, 1, 0.5, 7);
		PlayVoice("Kyo_Attack3");
		return;
	}

	if (_Key == "Mushiki1_Attack1")
	{
		AddHitBox(Vec2(50, 50), Vec2(50, 0), 0.1, 60 * m_Damage, 0 * m_Damage, Vec2(50, 0), 40, 1, 0.2, 7, "Fire");
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos + Vec2(m_Owner->m_Scale.x * 60, -55), Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Kyo_Mushiki_Fire1_");
		Anim->m_Speed = 0.05;
		Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, Vec2(m_Owner->m_Scale.x, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Kyo_Mushiki_Start_Fire");
		Anim->m_Speed = 0.05;
		SOUND->Play("Explosion1", -500);
		return;
	}

	if (_Key == "Mushiki2_Attack1")
	{
		AddHitBox(Vec2(50, 50), Vec2(50, 0), 0.1, 35 * m_Damage, 0 * m_Damage, Vec2(m_MushikiLoop * 100, 0), 40, 1, m_MushikiLoop == 0 ? 0.3 : 0, 4, "Fire");
		if (m_MushikiLoop == 0)
		{
			cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos + Vec2(m_Owner->m_Scale.x * 50, 0), Vec2(m_Owner->m_Scale.x, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
			Anim->m_Anim = IMAGE->FindAnimation("Kyo_182_Fire");
			Anim->m_Speed = 0.05;
		}
		return;
	}

	if (_Key == "Mushiki3_Attack1")
	{
		AddHitBox(Vec2(50, 50), Vec2(50, 0), 0.1, 35 * m_Damage, 0 * m_Damage, Vec2(m_MushikiLoop * 50, 0), 40, 1, m_MushikiLoop == 0 ? 0.3 : 0, 4, "Fire");
		return;
	}

	if (_Key == "Mushiki4_Attack1")
	{
		AddHitBox(Vec2(50, 50), Vec2(50, 0), 0.1, 35 * m_Damage, 0 * m_Damage, Vec2(m_MushikiLoop * 50, -250), 40, 1, m_MushikiLoop == 0 ? 0.3 : 0, 4, "Fire");
		return;
	}

	if (_Key == "Mushiki5_Attack1")
	{
		AddHitBox(Vec2(50, 50), Vec2(50, 0), 0.1, 75 * m_Damage, 0 * m_Damage, Vec2(250, -700), 40, 1, 0.4, 10, "Fire");
		SOUND->Play("Fire3", -500);
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos - Vec2(0, 50), m_Owner->m_Scale, 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Kyo_Oniyaki_Fire1");
		Anim->m_Speed = 0.05;
		return;
	}

	if (_Key == "Mushiki5_Effect1")
	{
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos - Vec2(0, 40), m_Owner->m_Scale, 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Kyo_Oniyaki_Fire2");
		Anim->m_Speed = 0.05;
		return;
	}
}

void cKyo::OnHit(string _Key, cObject * _Other, RECT _Rect)
{
	cPlayer::OnHit(_Key, _Other, _Rect);
	if (_Key == "GuardCancel")
	{
		_Other->GC(cCharacter)->m_SuperArmor = false;
	}
}

void cKyo::Death()
{
	cPlayer::Death();
	m_Owner->SetAlarm(6, SYSTEM->m_GameMode == GM_PvE ? 20 : 3);
}
