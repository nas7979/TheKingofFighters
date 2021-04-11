#pragma once
class cEnemy : public cCharacter
{
public:
	cEnemy();
	~cEnemy();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void OnCollision(cObject* _Other, RECT _Rect) override;
	void OnAnimationEnd(string _Key) override;
	void OnAnimationNotify(string _Key) override;
	void OnHit(string _Key, cObject* _Other, RECT _Rect) override;
	virtual void Death() override;

	float m_Range;
	cCharacter* m_Target;

	void SetTarget(cObject* _Target);
};

