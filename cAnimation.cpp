#include "DXUT.h"
#include "cAnimation.h"


cAnimation::cAnimation()
{
}


cAnimation::~cAnimation()
{
}

void cAnimation::Init()
{
	m_Frame = 1;
	m_Speed = 1;
	AC(cRenderer);
}

void cAnimation::Update()
{
	m_Frame += m_CurAnim->Speed * m_Speed * DT;
	if (m_Frame >= m_CurAnim->Size + 1)
	{
		if (m_CurAnim->Loop)
		{
			m_Frame = 1;
		}
		else
		{
			m_Frame = m_CurAnim->Size;
			m_Speed = 0;
		}
		for (auto& iter : m_Owner->m_Components)
		{
			iter->OnAnimationEnd(m_CurAnim->Key);
		}
	}

	if ((int)m_Frame != m_Last)
	{
		m_Last = (int)m_Frame;
		GC(cRenderer)->m_Image = (*m_CurAnim->Anim)[m_Last - 1];
		if (m_CurAnim->Notify[m_Last] != "")
		{
			for (auto& iter : m_Owner->m_Components)
			{
				iter->OnAnimationNotify(m_CurAnim->Notify[m_Last]);
			}
		}
	}
}

void cAnimation::Render()
{
}

void cAnimation::Release()
{
	for (auto& iter : m_Animations)
	{
		delete iter.second;
	}
}

void cAnimation::AddAnimation(string _Key, string _Resource, float _Speed, bool _Loop)
{
	Animation* a = new Animation;
	a->Key = _Key;
	a->Anim = IMAGE->FindAnimation(_Resource);
	a->Speed = 1 / _Speed;
	a->Loop = _Loop;
	a->Size = a->Anim->size();
	a->Notify.resize(a->Size + 1);
	m_Animations.insert(make_pair(_Key, a));
}

void cAnimation::AddNotify(string _Anim, int _Frame, string _Key)
{
	m_Animations[_Anim]->Notify[_Frame] = _Key;
}

void cAnimation::SetAnimation(string _Key)
{
	m_CurAnim = m_Animations[_Key];
	m_Speed = 1;
	m_Frame = 1;
	m_Last = 0;
	GC(cRenderer)->m_Image = (*m_CurAnim->Anim)[0];
}
