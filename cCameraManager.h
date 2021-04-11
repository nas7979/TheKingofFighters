#pragma once
#include "cSingleton.h"
class cCameraManager : public cSingleton<cCameraManager>
{
public:
	cCameraManager();
	~cCameraManager();

	void Init();
	void Update();
	void Render();
	void Release();

	Matrix m_Mat;
	Matrix m_InversedMat;
	Vec2 m_Pos;
	Vec2 m_ShakePos;
	float m_ShakeForce;
	float m_ShakeTime;
	float m_Scale;
	float m_ScaleTo;

	void Shake(float _Force, float _Time);
	void SetScale(float _Scale);
};

#define CAMERA cCameraManager::GetInstance()