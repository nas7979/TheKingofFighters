#pragma once
enum Pallete
{
	Pal_None,
	Pal_RedFire,
	Pal_PurpleFire,
	Pal_AfterImage
};
class cRenderer : public cComponent
{
public:
	cRenderer();
	~cRenderer();

	// cComponent을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	Texture* m_Image = nullptr;
	D3DCOLOR m_Color = 0xffffffff;
	int m_Fire = Pal_None;
	float m_ShadowOffset = 0;
	function<void()> m_PreRender = nullptr;
	function<void()> m_PostRender = nullptr;

	void SetFire(int _Fire);
};

