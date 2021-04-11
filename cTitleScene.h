#pragma once
class cTitleScene : public cScene
{
public:
	cTitleScene();
	~cTitleScene();

	// cScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	int m_Selected;
	bool m_InTitle;
	Vec2 m_Scale[4];
	wstring m_Text[4];
	D3DCOLOR m_Color[4];
};

