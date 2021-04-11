#pragma once
class cMissile : public cCharacter
{
public:
	cMissile();
	~cMissile();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void OnHit(string _Key, cObject* _Other, RECT _Rect) override;

	float m_Speed;
	float m_Dir;
	cObject* m_FiredBy;
};

