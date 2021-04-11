#pragma once
#include "cParticleBase.h"
#include "cParticle.h"
#include "cParticleBase.h"
#include "cParticleText.h"
#include "cParticleAnim.h"
class cParticleManager : public cSingleton<cParticleManager>
{
public:
	cParticleManager();
	~cParticleManager();

	void Init();
	void Update();
	void Render();
	void Release();

	list<cParticleBase*> m_Particles;

	template<typename T>
	T* AddParticle(Texture* _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Z, float _Depth, D3DCOLOR _Color = 0xffffffff)
	{
		T* a = new T;
		a->m_Image = _Image;
		a->m_Pos = _Pos;
		a->m_Sca = _Scale;
		a->m_Rot = _Rot;
		a->m_Z = _Z;
		a->m_Depth = _Depth;
		a->m_Color = _Color;
		m_Particles.push_back(a);
		return a;
	}
};

#define PART cParticleManager::GetInstance()