#pragma once
class cResultScene : public cScene
{
public:
	cResultScene();
	~cResultScene();

	// cScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	bool m_InTyping;
	wstring m_Name;
};

