#pragma once
#include "cPlayer.h"
class cIori_Player : public cPlayer
{
public:
	cIori_Player();
	~cIori_Player();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void OnCollision(cObject* _Other, RECT _Rect) override;
	void OnAnimationEnd(string _Key) override;
	void OnAnimationNotify(string _Key) override;
	void OnHit(string _Key, cObject* _Other, RECT _Rect) override;

	float m_Damage;
	bool m_Shift;
	bool m_CancelAble;
	int m_AoiPhase;
	vector<cCharacter*> m_Hited;
	bool m_Saika;

	void Death() override;
};

