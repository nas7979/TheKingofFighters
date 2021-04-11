#include "DXUT.h"
#include "cIori_Player.h"
#include "cEnemy.h"


cIori_Player::cIori_Player()
{
}


cIori_Player::~cIori_Player()
{
}

void cIori_Player::Init()
{
	cPlayer::Init();
	GC(cCollider)->Setting(Vec2(30, 50), Vec2(0, 0));
	GC(cRenderer)->m_ShadowOffset = -25;

	GC(cAnimation)->AddAnimation("Idle", m_Owner->m_Name + "_Idle", 0.1);
	GC(cAnimation)->AddAnimation("Walk", m_Owner->m_Name + "_Walk", 0.1);
	GC(cAnimation)->AddAnimation("Run", m_Owner->m_Name + "_Run", 0.07);
	GC(cAnimation)->AddAnimation("Wake", m_Owner->m_Name + "_Wake", 0.06);
	GC(cAnimation)->AddAnimation("Dodge", m_Owner->m_Name + "_Dodge", 0.0675);

	GC(cAnimation)->AddAnimation("WPunch", m_Owner->m_Name + "_WPunch", 0.055);
	GC(cAnimation)->AddNotify("WPunch", 2, "WPunch_Attack1");
	GC(cAnimation)->AddAnimation("WKick", m_Owner->m_Name + "_WKick", 0.07);
	GC(cAnimation)->AddNotify("WKick", 3, "WKick_Attack1");
	GC(cAnimation)->AddAnimation("SPunch", m_Owner->m_Name + "_SPunch", 0.055);
	GC(cAnimation)->AddNotify("SPunch", 5, "SPunch_Attack1");
	GC(cAnimation)->AddAnimation("SKick", m_Owner->m_Name + "_SKick", 0.08);
	GC(cAnimation)->AddNotify("SKick", 4, "SKick_Attack1");

	GC(cAnimation)->AddAnimation("WPunch_Air", m_Owner->m_Name + "_WPunch_Air", 0.11);
	GC(cAnimation)->AddNotify("WPunch_Air", 2, "WPunch_Air_Attack1");
	GC(cAnimation)->AddAnimation("WKick_Air", m_Owner->m_Name + "_WKick_Air", 0.11);
	GC(cAnimation)->AddNotify("WKick_Air", 2, "WKick_Air_Attack1");
	GC(cAnimation)->AddAnimation("SPunch_Air", m_Owner->m_Name + "_SPunch_Air", 0.07);
	GC(cAnimation)->AddNotify("SPunch_Air", 5, "SPunch_Air_Attack1");
	GC(cAnimation)->AddAnimation("SKick_Air", m_Owner->m_Name + "_SKick_Air", 0.1, false);
	GC(cAnimation)->AddNotify("SKick_Air", 2, "SKick_Air_Attack1");

	GC(cAnimation)->AddAnimation("Kuzu_Start", m_Owner->m_Name + "_Kuzu_Start", 0.045);
	GC(cAnimation)->AddNotify("Kuzu_Start", 1, "Kuzu_Start_Force1");
	GC(cAnimation)->AddAnimation("Kuzu_Hit", m_Owner->m_Name + "_Kuzu_Hit", 0.065);
	GC(cAnimation)->AddNotify("Kuzu_Hit", 7, "Kuzu_Hit_Attack1");
	GC(cAnimation)->AddAnimation("Kuzu_Miss", m_Owner->m_Name + "_Kuzu_Miss", 0.1);

	GC(cAnimation)->AddAnimation("Yami", m_Owner->m_Name + "_Yami", 0.07);
	GC(cAnimation)->AddNotify("Yami", 4, "Yami_FireMissile1");

	GC(cAnimation)->AddAnimation("Oniyaki", m_Owner->m_Name + "_Oniyaki", 0.06, false);
	GC(cAnimation)->AddNotify("Oniyaki", 4, "Oniyaki_Attack1");
	GC(cAnimation)->AddNotify("Oniyaki", 5, "Oniyaki_Attack2");
	GC(cAnimation)->AddNotify("Oniyaki", 6, "Oniyaki_Attack3");
	GC(cAnimation)->AddNotify("Oniyaki", 8, "Oniyaki_Fire1");
	GC(cAnimation)->AddAnimation("Oniyaki_End", m_Owner->m_Name + "_Oniyaki_End", 0.05);

	GC(cAnimation)->AddAnimation("Tsuma", m_Owner->m_Name + "_Tsuma", 0.06);
	GC(cAnimation)->AddNotify("Tsuma", 3, "Tsuma_Invincible1");
	GC(cAnimation)->AddNotify("Tsuma", 6, "Tsuma_Force1");
	GC(cAnimation)->AddNotify("Tsuma", 9, "Tsuma_Invincible2");
	GC(cAnimation)->AddNotify("Tsuma", 11, "Tsuma_Attack1");
	GC(cAnimation)->AddNotify("Tsuma", 12, "Tsuma_Speed1");
	GC(cAnimation)->AddNotify("Tsuma", 13, "Tsuma_Cancel1");
	GC(cAnimation)->AddNotify("Tsuma", 14, "Tsuma_Cancel1");

	GC(cAnimation)->AddAnimation("Aoi1", m_Owner->m_Name + "_Aoi1_", 0.065);
	GC(cAnimation)->AddNotify("Aoi1", 1, "Aoi1_Force1");
	GC(cAnimation)->AddNotify("Aoi1", 3, "Aoi1_Attack1");
	GC(cAnimation)->AddNotify("Aoi1", 5, "Aoi1_Cancel1");

	GC(cAnimation)->AddAnimation("Aoi2", m_Owner->m_Name + "_Aoi2_", 0.065);
	GC(cAnimation)->AddNotify("Aoi2", 3, "Aoi2_Attack1");
	GC(cAnimation)->AddNotify("Aoi2", 5, "Aoi2_Cancel1");

	GC(cAnimation)->AddAnimation("Aoi3", m_Owner->m_Name + "_Aoi3_", 0.08);
	GC(cAnimation)->AddNotify("Aoi3", 4, "Aoi3_Attack1");

	GC(cAnimation)->AddAnimation("Kingetsu_Start", m_Owner->m_Name + "_Kingetsu_Start", 0.04);
	GC(cAnimation)->AddAnimation("Kingetsu_Miss", m_Owner->m_Name + "_Kingetsu_Miss", 0.07);
	GC(cAnimation)->AddNotify("Kingetsu_Miss", 4, "Kingetsu_Miss_Attack1");
	GC(cAnimation)->AddNotify("Kingetsu_Miss", 6, "Kingetsu_Miss_Attack2");
	GC(cAnimation)->AddNotify("Kingetsu_Miss", 8, "Kingetsu_Miss_Check1");
	GC(cAnimation)->AddAnimation("Kingetsu_Hit", m_Owner->m_Name + "_Kingetsu_Hit", 0.06);
	GC(cAnimation)->AddNotify("Kingetsu_Hit", 2, "Kingetsu_Hit_Speed1");
	GC(cAnimation)->AddNotify("Kingetsu_Hit", 3, "Kingetsu_Hit_Attack1");
	GC(cAnimation)->AddAnimation("Kingetsu_NoTarget", m_Owner->m_Name + "_Kingetsu_NoTarget", 0.1);

	GC(cAnimation)->AddAnimation("Yaotome_Start", m_Owner->m_Name + "_Yaotome_Start", 0.04, false);
	GC(cAnimation)->AddNotify("Yaotome_Start", 3, "Yaotome_Start_Speed1");
	GC(cAnimation)->AddNotify("Yaotome_Start", 4, "Yaotome_Start_Speed2");

	GC(cAnimation)->AddAnimation("Yaotome_Charge", m_Owner->m_Name + "_Yaotome_Charge", 10, false);

	GC(cAnimation)->AddAnimation("Yaotome_Miss", m_Owner->m_Name + "_Yaotome_Miss", 0.3);

	GC(cAnimation)->AddAnimation("Yaotome", m_Owner->m_Name + "_Yaotome", 0.035);
	GC(cAnimation)->AddNotify("Yaotome", 4, "Yaotome_Attack1");
	GC(cAnimation)->AddNotify("Yaotome", 7, "Yaotome_Attack1");
	GC(cAnimation)->AddNotify("Yaotome", 14, "Yaotome_Attack1");
	GC(cAnimation)->AddNotify("Yaotome", 14, "Yaotome_Attack1");
	GC(cAnimation)->AddNotify("Yaotome", 22, "Yaotome_Attack2");
	GC(cAnimation)->AddNotify("Yaotome", 31, "Yaotome_Attack2");
	GC(cAnimation)->AddNotify("Yaotome", 35, "Yaotome_Attack2");
	GC(cAnimation)->AddNotify("Yaotome", 43, "Yaotome_Attack3");
	GC(cAnimation)->AddNotify("Yaotome", 48, "Yaotome_Speed1");
	GC(cAnimation)->AddNotify("Yaotome", 49, "Yaotome_Effect1");
	GC(cAnimation)->AddNotify("Yaotome", 51, "Yaotome_Speed2");
	GC(cAnimation)->AddNotify("Yaotome", 52, "Yaotome_Speed3");
	GC(cAnimation)->AddNotify("Yaotome", 53, "Yaotome_Attack4");
	GC(cAnimation)->AddNotify("Yaotome", 54, "Yaotome_Cancel1");

	GC(cAnimation)->AddAnimation("Saika", m_Owner->m_Name + "_Saika", 0.075);
	GC(cAnimation)->AddNotify("Saika", 2, "Saika_Speed1");
	GC(cAnimation)->AddNotify("Saika", 4, "Saika_Attack1");
	GC(cAnimation)->AddNotify("Saika", 5, "Saika_Attack1");
	GC(cAnimation)->AddNotify("Saika", 6, "Saika_Attack1");
	GC(cAnimation)->AddNotify("Saika", 10, "Saika_Attack2");
	GC(cAnimation)->AddNotify("Saika", 11, "Saika_Attack2");
	GC(cAnimation)->AddNotify("Saika", 12, "Saika_Attack2");
	GC(cAnimation)->AddNotify("Saika", 16, "Saika_Speed2");
	GC(cAnimation)->AddNotify("Saika", 28, "Saika_Attack3");

	GC(cAnimation)->AddAnimation("Saika_Loop", m_Owner->m_Name + "_Saika_Loop", 0.04);
	GC(cAnimation)->AddAnimation("Saika_End", m_Owner->m_Name + "_Saika_End", 0.1);

	GC(cAnimation)->SetAnimation("Idle");
	m_MaxHp = SYSTEM->m_PlayerRemain == 1 ? 1500 : 750;
	m_Hp = m_MaxHp;
	m_MaxStun = 100000;
	m_Stun = 100000;
	m_HitSound = 3;
	m_Shift = false;
	m_CancelAble = false;
	m_Killed = 0;
	m_Dealt = 0;
	m_Damage = 1;
	m_AoiPhase = 0;
	m_Saika = false;

	m_Owner->SetAlarmSize(10);
	m_Owner->SetAlarm(6, 0);
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
		{
			string Key = GC(cAnimation)->m_CurAnim->Key;
			if (Key == "Yaotome_Charge")
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
			m_Owner->SetAlarm(6, 0.08f);
			break;
		}

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
			if (GC(cAnimation)->m_CurAnim->Key == "Run")
			{
				GC(cAnimation)->SetAnimation("Kingetsu_NoTarget");
				AddForce(250, 0);
			}
			break;

		case 9:
			GC(cAnimation)->SetAnimation("Saika_End");
			break;
		}
	};
}

void cIori_Player::Update()
{
	if (GC(cAnimation)->m_CurAnim->Key == "Yaotome_Charge")
	{
		if (abs(m_Velocity.x) <= 200)
		{
			GC(cAnimation)->SetAnimation("Yaotome_Miss");
			if (m_HitBox != nullptr)
			{
				m_HitBox->m_Owner->m_Destroyed = true;
				m_HitBox = nullptr;
			}
		}
	}
	else if (GC(cAnimation)->m_CurAnim->Key == "Run" && m_MainState == State_Skill)
	{
		AddForce(500, 0);
	}

	cPlayer::Update();

	if (m_GaugeStock != 0 && GC(cAnimation)->m_CurAnim->Key == "Yaotome" && GC(cAnimation)->m_Frame >= 48 && GC(cAnimation)->m_Frame < 54)
	{
		if (INPUT->CheckCommand(Cmd_26262626, Key_WPunch, m_Side) || INPUT->CheckCommand(Cmd_26262626, Key_SPunch, m_Side))
		{
			m_Saika = true;
		}
	}
	if ((m_MainState == State_Idle || m_MainState == State_Walk || m_MainState == State_Run) || (m_CancelAble && m_MainState != State_Skill))
	{
		if (m_GaugeStock != 0)
		{
			if (INPUT->CheckCommand(Cmd_2624, Key_WPunch, m_Side) || INPUT->CheckCommand(Cmd_2624, Key_SPunch, m_Side))
			{
				if (m_SubState == State_Ground)
				{
					if ((m_MainState == State_Idle || m_MainState == State_Walk || m_MainState == State_Run))
					{
						m_Owner->m_Scale.x *= -1;
					}
					m_GaugeStock--;
					GC(cAnimation)->SetAnimation("Yaotome_Start");
					PlayVoice("Iori_Player_Yaotome_Start");
					cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos + Vec2(0, -60), Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
					Anim->m_Anim = IMAGE->FindAnimation("Flash");
					Anim->m_Speed = 0.035;
					SOUND->Play("Flash", 0);
					m_MainState = State_Skill;
				}
			}
		}

		if (INPUT->CheckCommand(Cmd_624, Key_WKick, m_Side) || INPUT->CheckCommand(Cmd_624, Key_SKick, m_Side))
		{
			if (m_SubState == State_Ground)
			{
				if ((m_MainState == State_Idle || m_MainState == State_Walk || m_MainState == State_Run))
				{
					m_Owner->m_Scale.x *= -1;
				}
				GC(cAnimation)->SetAnimation("Kingetsu_Start");
				m_MainState = State_Skill;
				PlayVoice("Iori_Player_Kingetsu_Start");
			}
		}

		if (INPUT->CheckCommand(Cmd_626, Key_WPunch, m_Side) || INPUT->CheckCommand(Cmd_626, Key_SPunch, m_Side))
		{
			if (m_SubState == State_Ground)
			{
				GC(cAnimation)->SetAnimation("Oniyaki");
				m_MainState = State_Skill;
				PlayVoice("Iori_Player_Oniyaki");
				AddForce(75, 0);
			}
		}
		

		if (INPUT->CheckCommand(Cmd_626, Key_WKick, m_Side) || INPUT->CheckCommand(Cmd_626, Key_SKick, m_Side))
		{
			if (m_SubState == State_Ground)
			{
				GC(cAnimation)->SetAnimation("Tsuma");
				m_MainState = State_Skill;
			}
		}

		if (INPUT->CheckCommand(Cmd_426, Key_WPunch, m_Side) || INPUT->CheckCommand(Cmd_426, Key_SPunch, m_Side))
		{
			if (m_SubState == State_Ground)
			{
				GC(cAnimation)->SetAnimation("Yami");
				PlayVoice("Iori_Player_Yami");
				m_MainState = State_Skill;
			}
		}

		if (INPUT->CheckCommand(Cmd_24, Key_WPunch, m_Side) || INPUT->CheckCommand(Cmd_24, Key_SPunch, m_Side))
		{
			if (m_SubState == State_Ground)
			{
				if ((m_MainState == State_Idle || m_MainState == State_Walk || m_MainState == State_Run))
				{
					m_Owner->m_Scale.x *= -1;
				}
				GC(cAnimation)->SetAnimation("Aoi1");
				PlayVoice("Iori_Player_Aoi1");
				m_MainState = State_Skill;
				m_AoiPhase = 1;
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
				PlayVoice("Iori_Player_Attack1");
				INPUT->m_InputStartZ[m_Side] = m_Owner->m_Z;
			}
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_WKick]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("WKick");
				PlayVoice("Iori_Player_Attack1");
				INPUT->m_InputStartZ[m_Side] = m_Owner->m_Z;
			}
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_SPunch]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("SPunch");
				PlayVoice("Iori_Player_Attack4");
				INPUT->m_InputStartZ[m_Side] = m_Owner->m_Z;
			}
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_SKick]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("SKick");
				PlayVoice("Iori_Player_Attack4");
				INPUT->m_InputStartZ[m_Side] = m_Owner->m_Z;
			}

			if (INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_WPunch]) && INPUT->KeyPress(INPUT->m_Keys[m_Side][Key_WKick]))
			{
				GC(cAnimation)->SetAnimation("Dodge");
				AddForce(500, 0);
				PlayVoice("Iori_Player_Dodge");
				m_MainState = State_Dodge;
			}
		}
		else
		{
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_WPunch]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("WPunch_Air");
				PlayVoice("Iori_Player_Attack1");
			}
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_WKick]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("WKick_Air");
				PlayVoice("Iori_Player_Attack1");
			}
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_SPunch]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("SPunch_Air");
				PlayVoice("Iori_Player_Attack4");
			}
			if (INPUT->KeyDown(INPUT->m_Keys[m_Side][Key_SKick]))
			{
				m_MainState = State_Attack;
				GC(cAnimation)->SetAnimation("SKick_Air");
				PlayVoice("Iori_Player_Attack4");
				m_Owner->m_Scale.x *= -1;
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
			GC(cAnimation)->SetAnimation("Kuzu_Start");
			SYSTEM->HitStop(0.5);
			cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, m_Owner->m_Scale, 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
			Anim->m_Anim = IMAGE->FindAnimation("GuardCancel");
			Anim->m_Speed = 0.005;
			cParticle* Part = PART->AddParticle<cParticle>(IMAGE->Find("Point"), Vec2(0, 0), Vec2(10000, 10000), 0, 0, 0.8);
			Part->SetAlpha(1000, -255 * 30 * 10, 1);
		}
	}

	if (m_AoiPhase != 0)
	{
		if (m_AoiPhase == 2 && (INPUT->CheckCommand(Cmd_24, Key_WPunch, m_Side) || INPUT->CheckCommand(Cmd_24, Key_SPunch, m_Side)))
		{
			m_AoiPhase = 3;
		}
		else if (m_AoiPhase == 5 && (INPUT->CheckCommand(Cmd_24, Key_WPunch, m_Side) || INPUT->CheckCommand(Cmd_24, Key_SPunch, m_Side)))
		{
			m_AoiPhase = 6;
		}
	}

	if (!m_Dead)
		m_Owner->m_Pos.x = Clamp(m_Owner->m_Pos.x, CAMERA->m_Pos.x - 960 / CAMERA->m_Scale, CAMERA->m_Pos.x + 960 / CAMERA->m_Scale);
}

void cIori_Player::Render()
{
	cPlayer::Render();
}

void cIori_Player::Release()
{
	cCharacter::Release();
	SYSTEM->m_Player[m_Side] = nullptr;
	if (m_Dead == false)
		SYSTEM->m_PlayerRemain--;
}

void cIori_Player::OnCollision(cObject * _Other, RECT _Rect)
{
	cPlayer::OnCollision(_Other, _Rect);
}

void cIori_Player::OnAnimationEnd(string _Key)
{
	cPlayer::OnAnimationEnd(_Key);
	m_Hited.clear();
	m_Saika = false;

	if (_Key == "WPunch" || _Key == "WKick" || _Key == "SPunch" || _Key == "SKick" || _Key == "WPunch_Air" || _Key == "WKick_Air" || _Key == "SPunch_Air" || _Key == "SKick_Air" ||
		_Key == "Dodge" || _Key == "Kuzu_Miss" || _Key == "Yami" || _Key == "Kingetsu_Miss" || _Key == "Kingetsu_NoTarget" || _Key == "Kingetsu_Hit" ||
		_Key == "Aoi1" || _Key == "Aoi2" || _Key == "Aoi3" || _Key == "Tsuma" || _Key == "Yaotome_Miss" || _Key == "Yaotome" || _Key == "Saika_End")
	{
		Idle();
		return;
	}

	if (_Key == "Kuzu_Hit")
	{
		Idle();
		m_Owner->m_Scale.x *= -1;
		return;
	}

	if (_Key == "Oniyaki")
	{
		GC(cAnimation)->SetAnimation("Oniyaki_End");
		m_MainState = State_Attack;
		return;
	}

	if (_Key == "Kingetsu_Start")
	{
		GC(cAnimation)->SetAnimation("Run");
		GC(cAnimation)->m_Speed = 1.2f;
		m_Owner->SetAlarm(8, 0.5f);
		AddHitBox(Vec2(40, 40), Vec2(40, 0), 0.49f, 0, 0, Vec2(0, 0), 30, 0, 0, 0, "Kingetsu_Check");
		return;
	}

	if (_Key == "Kuzu_Start")
	{
		GC(cAnimation)->SetAnimation("Kuzu_Miss");
		AddHitBox(Vec2(25, 1), Vec2(40, 50), 0.05f, 0, 0, Vec2(0, 0), 25, 3, 0, 0, "Kuzu_Hit");
		return;
	}

	if (_Key == "Yaotome_Start")
	{
		GC(cAnimation)->SetAnimation("Yaotome_Charge");
		AddHitBox(Vec2(40, 30), Vec2(20, 0), 10, 0, 0, Vec2(0, 0), 35, 1, 0, 0, "Yaotome_Charge");
		AddForce(m_SubState == State_Air ? 700 : 1000, 0);
		return;
	}

	if (_Key == "Saika")
	{
		GC(cAnimation)->SetAnimation("Saika_Loop");
		m_Owner->SetAlarm(9, 1);
		return;
	}
}

void cIori_Player::OnAnimationNotify(string _Key)
{
	cPlayer::OnAnimationNotify(_Key);

	if (_Key == "WPunch_Attack1")
	{
		AddHitBox(Vec2(35, 10), Vec2(30, -25), 0.05, 10 * m_Damage, 5 * m_Damage, Vec2(75, 0), 20, 0.3, 0.05, 2);
		m_CancelAble = true;
		m_Owner->SetAlarm(4, 0.13);
		return;
	}
	if (_Key == "WKick_Attack1")
	{
		AddHitBox(Vec2(35, 10), Vec2(50, -15), 0.1, 15 * m_Damage, 7 * m_Damage, Vec2(100, 0), 25, 0.4, 0.05, 2);
		m_CancelAble = true;
		m_Owner->SetAlarm(4, 0.1);
		return;
	}
	if (_Key == "SPunch_Attack1")
	{
		AddHitBox(Vec2(30, 30), Vec2(40, 0), 0.05, 20 * m_Damage, 10 * m_Damage, Vec2(175, 0), 30, 0.6, 0.08, 3);
		m_CancelAble = true;
		m_Owner->SetAlarm(4, 0.15);
		return;
	}
	if (_Key == "SKick_Attack1")
	{
		AddHitBox(Vec2(40, 10), Vec2(45, -25), 0.2, 30 * m_Damage, 15 * m_Damage, Vec2(250, 0), 40, 0.75, 0.15, 4);
		m_CancelAble = true;
		m_Owner->SetAlarm(4, 0.15);
		return;
	}

	if (_Key == "WPunch_Air_Attack1")
	{
		AddHitBox(Vec2(15, 15), Vec2(50, 20), 0.1, 10 * m_Damage, 10 * m_Damage, Vec2(50, 0), 20, 0.4, 0.1, 2);
		return;
	}
	if (_Key == "WKick_Air_Attack1")
	{
		AddHitBox(Vec2(40, 10), Vec2(50, -10), 0.15, 15 * m_Damage, 15 * m_Damage, Vec2(75, 0), 25, 0.6, 0.1, 2);
		return;
	}
	if (_Key == "SKick_Air_Attack1")
	{
		AddHitBox(Vec2(35, 20), Vec2(40, 15), 0.2, 25 * m_Damage, 25 * m_Damage, Vec2(-200, 0), 30, 0.8, 0.1, 3);
		return;
	}
	if (_Key == "SPunch_Air_Attack1")
	{
		AddHitBox(Vec2(25, 15), Vec2(30, 20), 0.25, 30 * m_Damage, 30 * m_Damage, Vec2(150, 750), 40, 0.8, 0.2, 5);
		return;
	}

	if (_Key == "Yami_FireMissile1")
	{
		AddHitBox(Vec2(35, 35), Vec2(0, 0), 100, 35 * m_Damage, 10 * m_Damage, Vec2(100, 0), 25, 0.5, 0.1, 5, "Iori_Hit");
		cObject* a = FireMissile("Iori_Yami_Missile", 0.1, m_Owner->m_Pos + Vec2(0, 15), 600, m_Owner->m_Scale.x == 1 ? 0 : 180)->m_Owner;
		a->SetAlarm(0, 10);
		a->m_Tag = Obj_Player;
		a->GC(cRenderer)->m_ShadowOffset = -15;
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, m_Owner->m_Scale, 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Iori_Yami_Fire");
		Anim->m_Speed = 0.07;
		GC(cAnimation)->m_Speed = 0.55f;
		return;
	}

	if (_Key == "Oniyaki_Attack1")
	{
		AddHitBox(Vec2(20, 40), Vec2(40, -30), 0.03, 25 * m_Damage, 20 * m_Damage, Vec2(30, 0), 30, 1, 0.1, 5, "IoriFire");
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos - Vec2(0, 40), m_Owner->m_Scale, 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Iori_Player_Oniyaki_Fire1_");
		Anim->m_Speed = 0.05;
		return;
	}
	if (_Key == "Oniyaki_Attack2")
	{
		AddHitBox(Vec2(20, 40), Vec2(40, -30), 0.03, 20 * m_Damage, 15 * m_Damage, Vec2(30, 0), 30, 1, 0.08, 4, "IoriFire");
		return;
	}
	if (_Key == "Oniyaki_Attack3")
	{
		AddForce(10, -700);
		AddHitBox(Vec2(20, 40), Vec2(40, -30), 0.03, 15 * m_Damage, 10 * m_Damage, Vec2(100, -800), 30, 1, 0.08, 3, "IoriFire");
		return;
	}
	if (_Key == "Oniyaki_Fire1")
	{
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos - Vec2(0, 30), m_Owner->m_Scale, 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Iori_Player_Oniyaki_Fire2_");
		Anim->m_Speed = 0.05;
	}

	if (_Key == "Kingetsu_Miss_Attack1")
	{
		AddHitBox(Vec2(30, 20), Vec2(30, -20), 0.01, 10 * m_Damage, 10 * m_Damage, Vec2(150, 0), 30, 1, 0.05, 3);
		return;
	}
	if (_Key == "Kingetsu_Miss_Attack2")
	{
		AddHitBox(Vec2(30, 35), Vec2(35, -25), 0.01, 10 * m_Damage, 10 * m_Damage, Vec2(40, 400), 30, 1, 0.075, 3, "Kingetsu_Hit");
		return;
	}
	if (_Key == "Kingetsu_Miss_Check1")
	{
		if (m_Hited.size() != 0)
		{
			GC(cAnimation)->SetAnimation("Kingetsu_Hit");
			GC(cRenderer)->m_Image = (*GC(cAnimation)->m_CurAnim->Anim)[0];
			PlayVoice("Iori_Player_Kingetsu_Hit");
		}
		return;
	}
	if (_Key == "Kingetsu_Hit_Speed1")
	{
		GC(cAnimation)->m_Speed = 0.12f;
		return;
	}
	if (_Key == "Kingetsu_Hit_Attack1")
	{
		Vec2 Pos;
		for (auto& iter : m_Hited)
		{
			iter->m_MainState = State_Hit;
			iter->m_Owner->SetAlarm(1, 0);
			Pos = iter->m_Owner->m_Pos - m_Owner->m_Pos;
			Pos.x *= m_Owner->m_Scale.x;
			AddHitBox(Vec2(1, 1), Pos, 0.01, 65 * m_Damage, 35 * m_Damage, Vec2(100, 1250), 0, 1, 0.2, 7, "IoriFire");
			m_HitBox->m_Owner->m_Z = iter->m_Owner->m_Z;
		}
		SOUND->Play("Explosion1", -500);
		m_Hited.clear();
		GC(cAnimation)->m_Speed = 0.5f;
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos + Vec2(60 * m_Owner->m_Scale.x, 10), Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Fire_Purple_Large3_");
		Anim->m_Speed = 0.05;
		return;
	}

	if (_Key == "Tsuma_Invincible1")
	{
		m_Invincible = true;
		return;
	}
	if (_Key == "Tsuma_Force1")
	{
		AddForce(150, -300);
		GC(cAnimation)->m_Speed = 0.65f;
		return;
	}
	if (_Key == "Tsuma_Invincible2")
	{
		m_Invincible = false;
		GC(cAnimation)->m_Speed = 0.8f;
		return;
	}
	if (_Key == "Tsuma_Attack1")
	{
		GC(cAnimation)->m_Speed = 0.75f;
		AddHitBox(Vec2(40, 30), Vec2(40, 0), 0.05, 50 * m_Damage, 25 * m_Damage, Vec2(175, 0), 30, 0.6, 0.1, 5, "IoriFire");
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, m_Owner->m_Scale, 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Iori_Player_Tsuma_Fire");
		Anim->m_Speed = 0.03;
		SOUND->Play("Fire2", -500);
		PlayVoice("Iori_Player_Tsuma");
		return;
	}
	if (_Key == "Tsuma_Speed1")
	{
		GC(cAnimation)->m_Speed = 0.3f;
		if (INPUT->CheckCommand(Cmd_24, Key_WPunch, m_Side) || INPUT->CheckCommand(Cmd_24, Key_SPunch, m_Side))
		{
			if (m_SubState == State_Ground)
			{
				if ((m_MainState == State_Idle || m_MainState == State_Walk || m_MainState == State_Run))
				{
					m_Owner->m_Scale.x *= -1;
				}
				GC(cAnimation)->SetAnimation("Aoi1");
				PlayVoice("Iori_Player_Aoi1");
				m_MainState = State_Skill;
				m_AoiPhase = 1;
			}
		}
		return;
	}
	if (_Key == "Tsuma_Cancel1")
	{
		GC(cAnimation)->m_Speed = 0.7f;
		if (INPUT->CheckCommand(Cmd_24, Key_WPunch, m_Side) || INPUT->CheckCommand(Cmd_24, Key_SPunch, m_Side))
		{
			if (m_SubState == State_Ground)
			{
				if ((m_MainState == State_Idle || m_MainState == State_Walk || m_MainState == State_Run))
				{
					m_Owner->m_Scale.x *= -1;
				}
				GC(cAnimation)->SetAnimation("Aoi1");
				PlayVoice("Iori_Player_Aoi1");
				m_MainState = State_Skill;
				m_AoiPhase = 1;
			}
		}
		return;
	}

	if (_Key == "Aoi1_Force1")
	{
		AddForce(250, 0);
		return;
	}
	if (_Key == "Aoi1_Attack1")
	{
		AddHitBox(Vec2(30, 30), Vec2(40, -40), 0.1, 20 * m_Damage, 15 * m_Damage, Vec2(200, 0), 20, 0.8, 0.075, 5);
		m_AoiPhase = 2;
		GC(cAnimation)->m_Speed = 0.5f;
		return;
	}
	if (_Key == "Aoi1_Cancel1")
	{
		if (m_AoiPhase == 3)
		{
			m_AoiPhase = 4;
			GC(cAnimation)->SetAnimation("Aoi2");
			PlayVoice("Iori_Player_Aoi2");
			AddForce(250, 0);
		}
		return;
	}

	if (_Key == "Aoi2_Attack1")
	{
		AddHitBox(Vec2(30, 30), Vec2(40, -40), 0.1, 25 * m_Damage, 22 * m_Damage, Vec2(250, -600), 20, 0.8, 0.075, 6);
		m_AoiPhase = 5;
		GC(cAnimation)->m_Speed = 0.65f;
		return;
	}

	if (_Key == "Aoi2_Cancel1")
	{
		if (m_AoiPhase == 6)
		{
			m_AoiPhase = 7;
			GC(cAnimation)->SetAnimation("Aoi3");
			PlayVoice("Iori_Player_Aoi3");
			AddForce(300, -500);
			GC(cAnimation)->m_Speed = 0.75f;
		}
		return;
	}

	if (_Key == "Aoi3_Attack1")
	{
		AddHitBox(Vec2(35, 30), Vec2(40, 0), 0.1, 35 * m_Damage, 30 * m_Damage, Vec2(200, 1250), 20, 0.8, 0.12, 8, "", true, 3);
		GC(cAnimation)->m_Speed = 0.6f;
		return;
	}

	if (_Key == "Kuzu_Start_Force1")
	{
		AddForce(75, 0);
		return;
	}
	if (_Key == "Kuzu_Hit_Attack1")
	{
		Vec2 Pos;
		for (auto& iter : m_Hited)
		{
			Pos = iter->m_Owner->m_Pos - m_Owner->m_Pos;
			Pos.x *= m_Owner->m_Scale.x;
			AddHitBox(Vec2(1, 1), Pos, 0.01, 0, 0, Vec2(-500, 0), 0, 1.5, 0, 0);
			m_HitBox->m_Owner->m_Z = iter->m_Owner->m_Z;
		}
		m_Hited.clear();
		PlayVoice("Iori_Player_Kuzu");
		return;
	}

	if (_Key == "Yaotome_Start_Speed1")
	{
		GC(cAnimation)->m_Speed = 0.2f;
		return;
	}
	if (_Key == "Yaotome_Start_Speed2")
	{
		GC(cAnimation)->m_Speed = 1;
		return;
	}
	
	if (_Key == "Yaotome_Attack1")
	{
		AddHitBox(Vec2(40, 40), Vec2(40, 0), 0.05, 15 * m_Damage, 0, Vec2(0, 0), 30, 0.4, 0, 0, "FireOff", true, 4);
		return;
	}
	if (_Key == "Yaotome_Attack2")
	{
		AddHitBox(Vec2(40, 40), Vec2(40, 0), 0.05, 15 * m_Damage, 0, Vec2(0, 0), 30, 0.4, 0, 0, "", true, 5);
		return;
	}
	if (_Key == "Yaotome_Attack3")
	{
		AddHitBox(Vec2(40, 40), Vec2(40, 0), 0.05, 15 * m_Damage, 0, Vec2(0, 0), 30, 1.5f, 0, 0, "", true, 5);
		return;
	}
	if (_Key == "Yaotome_Speed1")
	{
		GC(cAnimation)->m_Speed = 0.07f;
		return;
	}
	if (_Key == "Yaotome_Effect1")
	{
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos + Vec2(20 * m_Owner->m_Scale.x, -30), Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.02);
		Anim->m_Anim = IMAGE->FindAnimation("Throw");
		Anim->m_Speed = 0.05;
		SOUND->Play("Throw1", -500);
		GC(cAnimation)->m_Speed = 0.8f;
		AddHitBox(Vec2(40, 40), Vec2(40, 0), 0.05, 0, 0, Vec2(0, 0), 30, 10, 0, 0);
		return;
	}
	if (_Key == "Yaotome_Speed2")
	{
		GC(cAnimation)->m_Speed = 0.09f;
		return;
	}
	if (_Key == "Yaotome_Speed3")
	{
		GC(cAnimation)->m_Speed = 0.25f;
		return;
	}
	if (_Key == "Yaotome_Attack4")
	{
		AddHitBox(Vec2(40, 40), Vec2(40, 0), 0.05, 200 * m_Damage, 0, Vec2(200, -550), 30, 1, 0.2, 0, "YaotomeExplosion", true, 100);
		for (int i = 0; i < 3; i++)
		{
			cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos + Vec2(Random(25,75) * m_Owner->m_Scale.x, Random(-40,10)), Vec2(Random(0,1) == 0 ? 1 : -1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
			Anim->m_Anim = IMAGE->FindAnimation("Fire_Purple_Large3_");
			Anim->m_Speed = 0.05;
		}
		SOUND->Play("Explosion1", 0);
		GC(cAnimation)->m_Speed = 0.2f;
		CAMERA->Shake(8, 0.75f);
		return;
	}
	if (_Key == "Yaotome_Cancel1")
	{
		if (m_Saika)
		{
			m_Saika = false;
			GC(cAnimation)->SetAnimation("Saika");
			SYSTEM->m_TimeScale = 0.075f;
			SYSTEM->m_Alarm[0] = 1;
			cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos + Vec2(0, -50), Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
			Anim->m_Anim = IMAGE->FindAnimation("Flash");
			Anim->m_Speed = 0.0035;
			SOUND->Play("Flash", 0);
			PlayVoice("Iori_Player_Saika1");
			m_GaugeStock--;
		}
		return;
	}

	if (_Key == "Saika_Speed1")
	{
		GC(cAnimation)->m_Speed = 1;
		bool IsKyo = false;
		for (auto& iter : m_Hited)
		{
			if (iter->m_Owner->m_Name == "Kyo")
			{
				IsKyo = true;
				break;
			}
		}
		if (IsKyo == false)
		{
			PlayVoice(RandomText("Iori_Player_Saika", 2, 4));
		}
		else
		{
			PlayVoice("Iori_Player_Kyo");
		}
		return;
	}
	if (_Key == "Saika_Attack1")
	{
		Vec2 Pos;
		for (auto& iter : m_Hited)
		{
			iter->m_MainState = State_Hit;
			iter->m_Owner->SetAlarm(1, 0);
			Pos = iter->m_Owner->m_Pos - m_Owner->m_Pos;
			Pos.x *= m_Owner->m_Scale.x;
			AddHitBox(Vec2(1, 1), Pos, 0.01, 10 * m_Damage, 0 * m_Damage, Vec2(5, -300), 0, 1, 0.15, 0, "FireOff", true, 4);
			m_HitBox->m_Owner->m_Z = iter->m_Owner->m_Z;
		}
		return;
	}
	if (_Key == "Saika_Attack2")
	{
		Vec2 Pos;
		for (auto& iter : m_Hited)
		{
			Pos = iter->m_Owner->m_Pos - m_Owner->m_Pos;
			Pos.x *= m_Owner->m_Scale.x;
			AddHitBox(Vec2(1, 1), Pos, 0.01, 10 * m_Damage, 0 * m_Damage, Vec2(10, -750), 0, 1, 0.15, 0, "", true, 5);
			m_HitBox->m_Owner->m_Z = iter->m_Owner->m_Z;
		}
		return;
	}
	if (_Key == "Saika_Speed2")
	{
		GC(cAnimation)->m_Speed = 1.3f;
		return;
	}
	if (_Key == "Saika_Attack3")
	{
		Vec2 Pos;
		for (auto& iter : m_Hited)
		{
			Pos = iter->m_Owner->m_Pos - m_Owner->m_Pos;
			Pos.x *= m_Owner->m_Scale.x;
			AddHitBox(Vec2(1, 1), Pos, 0.01, 200 * m_Damage, 0 * m_Damage, Vec2(250, -700), 0, 1, 0, 0, "IoriFire", true, 100);
			m_HitBox->m_Owner->m_Z = iter->m_Owner->m_Z;
		}
		CAMERA->Shake(10, 0.75f);
		SOUND->Play("Explosion1", 0);
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos + Vec2(110 * m_Owner->m_Scale.x, -60), m_Owner->m_Scale, 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation("Iori_Player_Saika_Effect");
		Anim->m_Speed = 0.04f;
		m_Hited.clear();
		return;
	}
}

void cIori_Player::OnHit(string _Key, cObject * _Other, RECT _Rect)
{
	cPlayer::OnHit(_Key, _Other, _Rect);
	if (_Key == "Kingetsu_Check" && m_HitBox != nullptr)
	{
		GC(cAnimation)->SetAnimation("Kingetsu_Miss");
		AddForce(300, 0);
		m_HitBox->m_Owner->m_Destroyed = true;
		m_HitBox = nullptr;
		return;
	}

	if (_Key == "Kingetsu_Hit")
	{
		if (_Other->GC(cCharacter)->m_MainState != State_Guard)
		{
			m_Hited.push_back(_Other->GC(cCharacter));
		}
		return;
	}

	if (_Key == "Kuzu_Hit")
	{
		_Other->GC(cCharacter)->m_SuperArmor = false;
		_Other->GC(cCharacter)->m_MainState = State_Hit;
		GC(cAnimation)->SetAnimation("Kuzu_Hit");
		_Other->m_Pos = m_Owner->m_Pos + Vec2(Random(15.f, 30.f) * m_Owner->m_Scale.x, 0);
		_Other->m_Z = m_Owner->m_Z + Random(-5.f, 5.f);
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos + Vec2(20 * m_Owner->m_Scale.x, -30), Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.02);
		Anim->m_Anim = IMAGE->FindAnimation("Throw");
		Anim->m_Speed = 0.05;
		SOUND->Play("Throw1", -500);
		_Other->GC(cCharacter)->m_Velocity.x = 0;
		m_Hited.push_back(_Other->GC(cCharacter));
		return;
	}

	if (_Key == "Yaotome_Charge" && m_HitBox != nullptr)
	{
		if (_Other->GC(cCharacter)->m_MainState != State_Guard)
		{
			GC(cAnimation)->SetAnimation("Yaotome");
			PlayVoice("Iori_Player_Yaotome");
			m_HitBox->m_Owner->m_Destroyed = true;
			m_HitBox = nullptr;
			m_Velocity.x = 0;
			_Other->m_Pos.x = m_Owner->m_Pos.x + 30 * m_Owner->m_Scale.x;
			_Other->m_Z = m_Owner->m_Z - 1;
			if (_Other->GC(cCharacter)->m_SubState == State_Air)
			{
				_Other->GC(cCharacter)->m_SubState = State_Ground;
				_Other->GC(cCharacter)->m_Ground = nullptr;
				_Other->GC(cCharacter)->m_Velocity = Vec2(0, 0);
				_Other->m_Pos.y = m_Owner->m_Pos.y;
			}
		}
		else
		{
			GC(cAnimation)->SetAnimation("Yaotome_Miss");
			if (m_HitBox != nullptr)
			{
				m_HitBox->m_Owner->m_Destroyed = true;
				m_HitBox = nullptr;
			}
			AddForce(200, 0);
		}
		return;
	}

	if (_Key == "YaotomeExplosion")
	{
		if (_Other->GC(cCharacter)->m_MainState != State_Guard)
		{
			m_Hited.push_back(_Other->GC(cCharacter));
		}
		_Other->GC(cRenderer)->SetFire(Pal_PurpleFire);
		SOUND->Play(RandomText("Fire", 1, 3), -500);
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, _Other->m_Pos + Vec2(Random(-30, 30), Random(-40, 40)), Vec2(1, 1), 0, _Other->m_Z, _Other->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation(RandomText("Fire_Purple_Large", 1, 3, true));
		Anim->m_Speed = 0.05;
		return;
	}
}

void cIori_Player::Death()
{
	cPlayer::Death();
	m_Owner->SetAlarm(7, SYSTEM->m_GameMode == GM_PvE ? 20 : 3);
}