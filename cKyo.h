#pragma once
#include "cPlayer.h"
class cKyo : public cPlayer
{
public:
	cKyo();
	~cKyo();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void OnCollision(cObject* _Other, RECT _Rect) override;
	void OnAnimationEnd(string _Key) override;
	void OnAnimationNotify(string _Key) override;
	void OnHit(string _Key, cObject* _Other, RECT _Rect) override;

	int m_AragamiPhase;
	float m_182Charge;
	float m_RedCharge;
	float m_Damage;
	bool m_182Charging;
	bool m_RedCharging;
	bool m_Shift;
	bool m_CancelAble;
	int m_MushikiLoop;
	Vec2 m_MushikiPos;

	void Death() override;
};

