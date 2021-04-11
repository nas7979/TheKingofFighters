#include "DXUT.h"
#include "cObject.h"


cObject::cObject()
{
}


cObject::~cObject()
{
}

void cObject::Init()
{
}

void cObject::Update()
{
	for (auto& iter : m_Components)
	{
		if (iter->m_Enable)
			iter->Update();
	}
	for (int i = 0; i < m_AlarmSize; i++)
	{
		m_Alarm[i] -= DT;
		if (m_Alarm[i] <= 0)
		{
			m_Alarm[i] = 1000000;
			m_AlarmFunc(i);
		}
	}
}

void cObject::Render()
{
	for (auto& iter : m_Components)
	{
		if (iter->m_Enable)
			iter->Render();
	}
}

void cObject::Release()
{
	for (auto& iter : m_Components)
	{
		iter->Release();
		delete iter;
	}
	SAFE_DELETE(m_Alarm);
}

void cObject::SetAlarm(int _Index, float _Time)
{
	m_Alarm[_Index] = _Time;
}

void cObject::SetAlarmSize(int _Size)
{
	m_Alarm = new float[_Size];
	m_AlarmSize = _Size;
	for (int i = 0; i < _Size; i++)
	{
		m_Alarm[i] = 1000000;
	}
}
