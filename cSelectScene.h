#pragma once
enum Character
{
	Char_Kyo,
	Char_Kim,
	Char_Iori,
	Char_End
};
class cSelectScene : public cScene
{
public:
	cSelectScene();
	~cSelectScene();

	// cScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	int m_Selected[2];
	int m_ModeSelected;
	bool m_IsSelected[2];
	int m_CharacterAmount;
	vector<cObject*> m_Characters[2];
};

