#pragma once
class cItem : public cComponent
{
public:
	cItem();
	~cItem();

	// cComponent��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	void OnCollision(cObject* _Other, RECT _Rect);

	float m_Pos;
};

