#pragma once
class cParticleBase
{
public:
	cParticleBase();
	virtual ~cParticleBase();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	Texture* m_Image = nullptr;
	D3DCOLOR m_Color = 0xffffffff;
	float m_Depth = 0;
	float m_Z = 0;

	Vec2 m_Pos;
	Vec2 m_PosVel = Vec2(0, 0);
	float m_PosFri = 1;

	Vec2 m_Sca;
	Vec2 m_ScaVel = Vec2(0, 0);
	float m_ScaFri = 1;

	float m_Rot;
	float m_RotVel = 0;
	float m_RotFri = 1;

	float m_Alp = 255;
	float m_AlpVel = 0;
	float m_AlpFri = 1;

	void SetPos(Vec2 _Vel, float _Fri);
	void SetScale(Vec2 _Vel, float _Fri);
	void SetRot(float _Vel, float _Fri);
	void SetAlpha(float _Alpha, float _Vel, float _Fri);
};

