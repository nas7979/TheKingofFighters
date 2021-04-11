#pragma once
class cPlayer : public cCharacter
{
public:
	cPlayer();
	~cPlayer();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void OnCollision(cObject* _Other, RECT _Rect) override;
	void OnAnimationEnd(string _Key) override;
	void OnAnimationNotify(string _Key) override;
	void OnHit(string _Key, cObject* _Other, RECT _Rect) override;

	int m_Killed;
	int m_Dealt;
	int m_Side;
	int m_GaugeStock;
	float m_Gauge;

	void Death() override;
	virtual void AddHitBox(Vec2 _Size, Vec2 _Pos, float _Time, float _Damage, float _Stun, Vec2 _Force, float _Z, float _HitTime, float _StopTime, float _Shake, string _Event = "", bool _DodgeAble = true, int _EffectSize = 0) override;
	void SetSide(int _Side);
	void AddGauge(int _Gauge);
};

