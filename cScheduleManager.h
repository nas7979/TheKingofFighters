#pragma once
struct Schedule
{
	function<bool()> Func;
	float Time;
	bool Once;
};
class cScheduleManager : public cSingleton<cScheduleManager>
{
public:
	cScheduleManager();
	~cScheduleManager();

	void Init();
	void Update();
	void Render();
	void Release();

	list<Schedule*> m_Schedules;

	void AddSchedule(float _Time, bool _Once, function<bool()> _Func);
};

#define SCHEDULE cScheduleManager::GetInstance()