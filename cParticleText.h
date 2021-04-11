#pragma once
class cParticleText : public cParticleBase
{
public:
	cParticleText();
	~cParticleText();

	void Render() override;

	wstring m_Text;
};

