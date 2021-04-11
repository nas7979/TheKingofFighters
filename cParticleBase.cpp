#include "DXUT.h"
#include "cParticleBase.h"


cParticleBase::cParticleBase()
{
}


cParticleBase::~cParticleBase()
{
}

void cParticleBase::Init()
{
}

void cParticleBase::Update()
{
}

void cParticleBase::Render()
{
	IMAGE->CenterRender(m_Image, m_Pos - Vec2(0, m_Z), m_Sca, m_Rot, m_Depth, m_Color);
}

void cParticleBase::Release()
{
}

void cParticleBase::SetPos(Vec2 _Vel, float _Fri)
{
	m_PosVel = _Vel;
	m_PosFri = _Fri;
}

void cParticleBase::SetScale(Vec2 _Vel, float _Fri)
{
	m_ScaVel = _Vel;
	m_ScaFri = _Fri;
}

void cParticleBase::SetRot(float _Vel, float _Fri)
{
	m_RotVel = _Vel;
	m_RotFri = _Fri;
}

void cParticleBase::SetAlpha(float _Alpha, float _Vel, float _Fri)
{
	m_Alp = _Alpha;
	m_AlpVel = _Vel;
	m_AlpFri = _Fri;
}
