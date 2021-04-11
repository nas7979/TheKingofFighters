#pragma once
class cCollider : public cComponent
{
public:
	cCollider();
	~cCollider();

	// cComponent을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	Vec2 m_Size;
	Vec2 m_Offset;
	RECT m_Rect;
	vector<ObjectTag> m_CollWith;

	void Setting(Vec2 _Pos, Vec2 _Offset);
};

