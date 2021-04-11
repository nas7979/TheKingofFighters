#pragma once
class cCharacter;
class cHitBox : public cComponent
{
public:
	cHitBox();
	~cHitBox();

	// cComponent을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void OnCollision(cObject* _Other, RECT _Rect);

	float m_Damage;
	float m_Stun;
	float m_HitTime;
	float m_StopTime;
	float m_Z;
	float m_Shake;
	float m_ForceMultiplyer = 1;
	Vec2 m_Force;
	int m_Size;
	bool m_DodgeAble;
	string m_Event;
	cCharacter* m_Character;
	vector<cObject*> m_Hited;
};

