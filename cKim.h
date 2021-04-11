#pragma once
#include "cPlayer.h"
class cKim : public cPlayer
{
public:
	cKim();
	~cKim();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void OnCollision(cObject* _Other, RECT _Rect) override;
	void OnAnimationEnd(string _Key) override;
	void OnAnimationNotify(string _Key) override;
	void OnHit(string _Key, cObject* _Other, RECT _Rect) override;

	int m_SanengekiPhase;
	float m_Damage;
	bool m_Shift;
	bool m_CancelAble;

	void Death() override;
};

