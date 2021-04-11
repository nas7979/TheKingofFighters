#include "DXUT.h"
#include "cRenderer.h"


cRenderer::cRenderer()
{
}


cRenderer::~cRenderer()
{
}

void cRenderer::Init()
{
}

void cRenderer::Update()
{
	if (m_Fire == Pal_RedFire)
	{
		if (Random(0, (int)(0.25f / DT)) == 0)
		{
			cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
			Anim->m_Anim = IMAGE->FindAnimation(RandomText("Fire_Small", 1, 2, true));
			Anim->m_Speed = 0.05;
		}
	}
	else if (m_Fire == Pal_PurpleFire)
	{
		if (Random(0, (int)(0.25f / DT)) == 0)
		{
			cParticleAnim* Anim = PART->AddParticle<cParticleAnim>(NULL, m_Owner->m_Pos, Vec2(1, 1), 0, m_Owner->m_Z, m_Owner->m_Depth - 0.01);
			Anim->m_Anim = IMAGE->FindAnimation(RandomText("Fire_Purple_Small", 1, 2, true));
			Anim->m_Speed = 0.05;
		}
	}
}

void cRenderer::Render()
{
	if(m_PreRender) m_PreRender();
	IMAGE->CenterRender(m_Image, m_Owner->m_Pos - Vec2(0, m_Owner->m_Z), m_Owner->m_Scale, m_Owner->m_Rot, m_Owner->m_Depth, m_Color);
	if(m_PostRender) m_PostRender();
	IMAGE->CenterRender(m_Image, Vec2(m_Owner->m_Pos.x, -m_Owner->m_Z + m_ShadowOffset), Vec2(m_Owner->m_Scale.x, 0.5), m_Owner->m_Rot, 0.8, 0x90000000);
}

void cRenderer::Release()
{
	if (m_Fire)
	{
		IMAGE->m_Fire.remove(this);
	}
}

void cRenderer::SetFire(int _Fire)
{
	if (m_Fire == 0 && _Fire != 0)
	{
		m_Fire = _Fire;
		IMAGE->m_Fire.push_back(this);
	}
	if (m_Fire != 0 && _Fire == 0)
	{
		m_Fire = _Fire;
		IMAGE->m_Fire.remove(this);
	}
}
