#pragma once
class cParticleAnim : public  cParticleBase
{
public:
	cParticleAnim();
	~cParticleAnim();

	void Update() override;
	void Render() override;

	vector<Texture*>* m_Anim;
	float m_Speed = 1;
	float m_Frame = 1;
};

