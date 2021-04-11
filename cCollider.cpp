#include "DXUT.h"
#include "cCollider.h"


cCollider::cCollider()
{
}


cCollider::~cCollider()
{
}

void cCollider::Init()
{
}

void cCollider::Update()
{
	Vec2 Pos = m_Owner->m_Pos + Vec2(m_Offset.x * m_Owner->m_Scale.x, m_Offset.y);
	m_Rect.left = Pos.x - m_Size.x;
	m_Rect.right = Pos.x + m_Size.x;
	m_Rect.top = Pos.y - m_Size.y;
	m_Rect.bottom = Pos.y + m_Size.y;
}

void cCollider::Render()
{
	if (SYSTEM->m_Debug)
	{
		IMAGE->CenterRender(IMAGE->Find("Point"), m_Owner->m_Pos + Vec2(m_Offset.x * m_Owner->m_Scale.x, m_Offset.y), m_Size * 2, 0, 0.7, 0x90ff00ff);
	}
}

void cCollider::Release()
{
}

void cCollider::Setting(Vec2 _Size, Vec2 _Offset)
{
	m_Size = _Size;
	m_Offset = _Offset;
	Vec2 Pos = m_Owner->m_Pos + Vec2(m_Offset.x * m_Owner->m_Scale.x, m_Offset.y);
	m_Rect.left = Pos.x - m_Size.x;
	m_Rect.right = Pos.x + m_Size.x;
	m_Rect.top = Pos.y - m_Size.y;
	m_Rect.bottom = Pos.y + m_Size.y;
}
