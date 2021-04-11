#pragma once
#include "cSelectScene.h"
class cStage1Scene : public cScene
{
public:
	cStage1Scene();
	~cStage1Scene();

	// cScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_CameraMin;
	float m_CameraMax;
	Character m_Characters[2];
	int m_Phase;
	int m_Player;

	void AddEnemy();
};

