#include "DXUT.h"
#include "cItem.h"


cItem::cItem()
{
}


cItem::~cItem()
{
}

void cItem::Init()
{
	m_Pos = 0;
	if (m_Owner->m_Name == "Item_Hp")
	{
		AC(cAnimation)->AddAnimation("Idle", "Item_Hp", 100);
	}
	GC(cAnimation)->SetAnimation("Idle");
	AC(cCollider)->Setting(Vec2(20, 20), Vec2(0, 0));
	GC(cCollider)->m_CollWith.push_back(Obj_Player);
}

void cItem::Update()
{
	m_Owner->m_Pos.y += cos(m_Pos) * 15 * DT;
	m_Pos += 10 * DT;
}

void cItem::Render()
{
}

void cItem::Release()
{
}

void cItem::OnCollision(cObject * _Other, RECT _Rect)
{
	if (abs(m_Owner->m_Z - _Other->m_Z) <= 30)
	{
		cCharacter* Player = _Other->GC(cCharacter);
		m_Owner->m_Destroyed = true;
		if (m_Owner->m_Name == "Item_Hp")
		{
			Player->m_Hp = Clamp(Player->m_Hp + Player->m_MaxHp * 0.2, 0, Player->m_MaxHp);
			cParticleText* PTex = PART->AddParticle<cParticleText>(NULL, m_Owner->m_Pos, Vec2(0.6, 0.6), 0, m_Owner->m_Z, 0.2, 0xffff0000);
			PTex->m_Text = L"체력 20% 회복";
			PTex->SetPos(Vec2(0, -400), 0.97);
			PTex->SetAlpha(400, -255, 1);
		}
	}
}
