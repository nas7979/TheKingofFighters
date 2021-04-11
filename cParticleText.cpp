#include "DXUT.h"
#include "cParticleText.h"


cParticleText::cParticleText()
{
}


cParticleText::~cParticleText()
{
}

void cParticleText::Render()
{
	IMAGE->CenterRenderText(m_Text, m_Pos - Vec2(0, m_Z), m_Sca, m_Rot, m_Depth, m_Color, m_Depth <= 0.1);
}
