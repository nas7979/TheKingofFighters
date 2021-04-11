#include "DXUT.h"
#include "cGround.h"


cGround::cGround()
{
}


cGround::~cGround()
{
}

void cGround::Init()
{
	AC(cCollider)->m_CollWith.push_back(Obj_Player);
	GC(cCollider)->m_CollWith.push_back(Obj_Enemy);
}

void cGround::Update()
{
	m_Owner->m_Depth = 0.3 + (m_Owner->m_Z + m_Z) * 0.001;
}

void cGround::Render()
{
}

void cGround::Release()
{
}

void cGround::Setting(Vec2 _Size, Vec2 _Offset, float _Z)
{
	GC(cCollider)->Setting(_Size, _Offset);
	m_Z = _Z;
}
