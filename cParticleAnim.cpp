#include "DXUT.h"
#include "cParticleAnim.h"


cParticleAnim::cParticleAnim()
{
}


cParticleAnim::~cParticleAnim()
{
}

void cParticleAnim::Update()
{
	m_Frame += (1 / m_Speed) * DT;
	if (m_Frame >= m_Anim->size())
	{
		m_Alp = 0;
	}
}

void cParticleAnim::Render()
{
	IMAGE->CenterRender((*m_Anim)[(int)m_Frame], m_Pos - Vec2(0, m_Z), m_Sca, m_Rot, m_Depth, m_Color);
}
