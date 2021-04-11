#pragma once
#include "cEnemy.h"
class cBig : public cEnemy
{
public:
	cBig();
	~cBig();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void OnCollision(cObject* _Other, RECT _Rect) override;
	void OnAnimationEnd(string _Key) override;
	void OnAnimationNotify(string _Key) override;
	void OnHit(string _Key, cObject* _Other, RECT _Rect) override;
};

