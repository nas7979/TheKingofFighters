#include "DXUT.h"
#include "cCameraManager.h"


cCameraManager::cCameraManager()
{
}


cCameraManager::~cCameraManager()
{
}

void cCameraManager::Init()
{
	m_ShakePos = Vec2(0, 0);
	m_ShakeForce = 0;
	m_Scale = 1;
	m_ScaleTo = 1;
}

void cCameraManager::Update()
{
	if (m_ShakeForce != 0)
	{
		m_ShakeForce -= m_ShakeTime * DT;
		if (m_ShakeForce <= 0)
		{
			m_ShakeForce = 0;
			m_ShakePos = Vec2(0, 0);
		}
		else
		{
			m_ShakePos = Vec2(Random(-m_ShakeForce, m_ShakeForce), Random(-m_ShakeForce, m_ShakeForce));
		}
	}
	if (m_ScaleTo != m_Scale)
	{
		m_Scale = Lerp<float>(m_Scale, m_ScaleTo, 0.15f * 60.f * NSDT);
		if (abs(m_Scale - m_ScaleTo) <= 0.001f)
		{
			m_Scale = m_ScaleTo;
		}
	}
	Matrix p, s;
	D3DXMatrixTranslation(&p, -m_Pos.x + 960 / m_Scale + m_ShakePos.x, -m_Pos.y + 540 / m_Scale + m_ShakePos.y, 0);
	D3DXMatrixScaling(&s, m_Scale, m_Scale, 1);
	m_Mat = p * s;
	D3DXMatrixInverse(&m_InversedMat, NULL, &m_Mat);
}

void cCameraManager::Render()
{
	g_Device->SetTransform(D3DTS_VIEW, &m_Mat);
}

void cCameraManager::Release()
{
}

void cCameraManager::Shake(float _Force, float _Time)
{
	if (SYSTEM->m_PlayerRemain == 2)
		_Force *= 0.5f;
	m_ShakeForce = _Force;
	m_ShakeTime = _Force / _Time;
}

void cCameraManager::SetScale(float _Scale)
{
	m_Scale = _Scale;
	m_ScaleTo = _Scale;
}
