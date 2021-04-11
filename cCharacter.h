#pragma once
#include "cHitBox.h"
#include "cGround.h"
class cMissile;
enum State
{
	State_Idle,
	State_Walk,
	State_Run,
	State_Attack,
	State_Skill,
	State_Guard,
	State_Stun,
	State_Hit,
	State_Down,
	State_Dodge,
	State_Ground,
	State_Air
};
class cCharacter : public cComponent
{
public:
	cCharacter();
	virtual ~cCharacter();

	// cComponent을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void OnAnimationEnd(string _Key) override;
	virtual void OnAnimationNotify(string _Key) override;
	virtual void OnCollision(cObject* _Other, RECT _Rect) override;
	virtual void OnHit(string _Key, cObject* _Other, RECT _Rect);

	virtual void Idle();
	virtual void Move();
	virtual void Jump();
	virtual void Stun();
	virtual void Death();
	void PlayVoice(string _Key, long _Volume = -500);
	void AddForce(float _X, float _Y);
	virtual void AddHitBox(Vec2 _Size, Vec2 _Pos, float _Time, float _Damage, float _Stun, Vec2 _Force, float _Z, float _HitTime, float _StopTime, float _Shake, string _Event = "", bool _DodgeAble = true, int _EffectSize = 0);
	cMissile* FireMissile(string _Anim,float _AnimSpeed, Vec2 _Pos, float _Speed, float _Dir);

	float m_Hp;
	float m_MaxHp;
	float m_Stun;
	float m_MaxStun;
	float m_Speed;
	float m_TargetZ;
	int m_HitSound;
	cGround* m_Ground = nullptr;
	cHitBox* m_HitBox = nullptr;
	State m_MainState;
	State m_SubState;
	Vec2 m_Velocity;
	LPDIRECTSOUNDBUFFER m_Voice = nullptr;
	bool m_InStun;
	bool m_Invincible;
	bool m_AlwaysSuper;
	bool m_SuperArmor;
	bool m_GuardPoint;
	bool m_GuardPointHited;
	bool m_Dead;

};

