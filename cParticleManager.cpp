#include "DXUT.h"
#include "cParticleManager.h"


cParticleManager::cParticleManager()
{
}


cParticleManager::~cParticleManager()
{
}

void cParticleManager::Init()
{
}

void cParticleManager::Update()
{
	for (auto& iter = m_Particles.begin(); iter != m_Particles.end();)
	{
		(*iter)->m_PosVel *= pow((*iter)->m_PosFri, DT * 60);
		(*iter)->m_ScaVel *= pow((*iter)->m_ScaFri, DT * 60);
		(*iter)->m_RotVel *= pow((*iter)->m_RotFri, DT * 60);
		(*iter)->m_AlpVel *= pow((*iter)->m_AlpFri, DT * 60);

		(*iter)->m_Pos += (*iter)->m_PosVel * DT;
		(*iter)->m_Sca += (*iter)->m_ScaVel * DT;
		(*iter)->m_Rot += (*iter)->m_RotVel * DT;
		(*iter)->m_Alp += (*iter)->m_AlpVel * DT;

		(*iter)->m_Color = ((*iter)->m_Color & 0x00ffffff) | (min(255, (int)(*iter)->m_Alp) << 24);
		(*iter)->Update();

		if ((*iter)->m_Alp <= 0 || (*iter)->m_Sca.y <= 0)
		{
			(*iter)->Release();
			delete *iter;
			iter = m_Particles.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void cParticleManager::Render()
{
	for (auto& iter : m_Particles)
	{
		iter->Render();
	}
}

void cParticleManager::Release()
{
	for (auto& iter : m_Particles)
	{
		iter->Release();
		delete iter;
	}
	m_Particles.clear();
}
