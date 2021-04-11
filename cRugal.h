#pragma once
#include "cEnemy.h"
class cRugal : public cEnemy
{
public:
	cRugal();
	~cRugal();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void OnCollision(cObject* _Other, RECT _Rect) override;
	void OnAnimationEnd(string _Key) override;
	void OnAnimationNotify(string _Key) override;
	void OnHit(string _Key, cObject* _Other, RECT _Rect) override;

	bool m_Intro;
	cObject* m_PressHited;
};

