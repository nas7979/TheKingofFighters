#pragma once
class cLoadingScene : public cScene
{
public:
	cLoadingScene();
	~cLoadingScene();

	// cScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void LoadImage(string _Path);
	void LoadSound(string _Path);
};

