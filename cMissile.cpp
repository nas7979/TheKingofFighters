#include "DXUT.h"
#include "cMissile.h"


cMissile::cMissile()
{
}


cMissile::~cMissile()
{
}

void cMissile::Init()
{
	AC(cAnimation);
	m_Owner->SetAlarmSize(1);
	m_Owner->m_AlarmFunc = [&](int _Index)->void {
		m_HitBox->m_Owner->m_Destroyed = true;
		m_HitBox = nullptr;
		m_Owner->m_Destroyed = true;
	};
}

void cMissile::Update()
{
	m_Owner->m_Pos += Vec2(m_Speed * cos(D3DXToRadian(m_Dir)), m_Speed * sin(D3DXToRadian(m_Dir))) * DT;
}

void cMissile::Render()
{
}

void cMissile::Release()
{
}

void cMissile::OnHit(string _Key, cObject * _Other, RECT _Rect)
{
	if (_Key == "Hit")
	{
		if (m_HitBox != nullptr)
		{
			m_HitBox->m_Owner->m_Destroyed = true;
			m_HitBox = nullptr;
			m_Owner->m_Destroyed = true;
		}
		return;
	}

	if (_Key == "182_Hit")
	{
		_Other->GC(cRenderer)->SetFire(Pal_RedFire);
		SOUND->Play(RandomText("Fire", 1, 3), -500);
		SOUND->Play("Kyo_182_End_Fire", -500);
		cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, _Other->m_Pos + Vec2(Random(-30, 30), Random(-40, 40)), Vec2(1, 1), 0, _Other->m_Z, _Other->m_Depth - 0.01);
		Anim->m_Anim = IMAGE->FindAnimation(RandomText("Fire_Large", 1, 3, true));
		Anim->m_Speed = 0.05;
		return;
	}

	if (_Key == "Iori_Hit")
	{
		_Other->GC(cRenderer)->SetFire(Pal_PurpleFire);
		SOUND->Play(RandomText("Fire", 1, 3), -500);
		if (m_HitBox != nullptr)
		{
			m_HitBox->m_Owner->m_Destroyed = true;
			m_HitBox = nullptr;
			m_Owner->m_Destroyed = true;
		}
		return;
	}
}
