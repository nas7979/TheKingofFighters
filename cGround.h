#pragma once
class cGround : public cComponent
{
public:
	cGround();
	~cGround();

	// cComponent��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Z;

	void Setting(Vec2 _Size, Vec2 _Offset, float _Z);
};

