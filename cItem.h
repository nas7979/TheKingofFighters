#pragma once
class cItem : public cComponent
{
public:
	cItem();
	~cItem();

	// cComponent을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	void OnCollision(cObject* _Other, RECT _Rect);

	float m_Pos;
};

