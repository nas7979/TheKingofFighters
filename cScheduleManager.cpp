#include "DXUT.h"
#include "cScheduleManager.h"


cScheduleManager::cScheduleManager()
{
}


cScheduleManager::~cScheduleManager()
{
}

void cScheduleManager::Init()
{
}

void cScheduleManager::Update()
{
	for (auto& iter = m_Schedules.begin(); iter != m_Schedules.end();)
	{
		(*iter)->Time -= DT;
		if ((*iter)->Once == true)
		{
			if ((*iter)->Time <= 0)
			{
				(*iter)->Func();
				delete *iter;
				iter = m_Schedules.erase(iter);
			}
			else
			{
				iter++;
			}
		}
		else
		{
			if ((*iter)->Func() == false || (*iter)->Time <= 0)
			{
				delete *iter;
				iter = m_Schedules.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
}

void cScheduleManager::Render()
{
}

void cScheduleManager::Release()
{
	for (auto& iter : m_Schedules)
	{
		delete iter;
	}
	m_Schedules.clear();
}

void cScheduleManager::AddSchedule(float _Time, bool _Once, function<bool()> _Func)
{
	Schedule* a = new Schedule;
	a->Func = _Func;
	a->Time = _Time;
	a->Once = _Once;
	m_Schedules.push_back(a);
}
