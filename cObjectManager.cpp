#include "DXUT.h"
#include "cObjectManager.h"


cObjectManager::cObjectManager()
{
}


cObjectManager::~cObjectManager()
{
}

void cObjectManager::Init()
{
}

void cObjectManager::Update()
{
	for (int Tag = 0; Tag < Obj_End; Tag++)
	{
		for (auto& iter = m_Objects[Tag].begin(); iter != m_Objects[Tag].end();)
		{
			if ((*iter)->m_Destroyed == true)
			{
				(*iter)->Release();
				delete *iter;
				iter = m_Objects[Tag].erase(iter);
			}
			else
			{
				(*iter)->Update();
				CheckCollision(*iter);
				iter++;
			}
		}
	}
}

void cObjectManager::Render()
{
	for (int Tag = 0; Tag < Obj_End; Tag++)
	{
		for (auto& iter : m_Objects[Tag])
		{
			iter->Render();
		}
	}
}

void cObjectManager::Release()
{
	for (int Tag = 0; Tag < Obj_End; Tag++)
	{
		for (auto& iter : m_Objects[Tag])
		{
			iter->Release();
			delete iter;
		}
		m_Objects[Tag].clear();
	}
}

cObject * cObjectManager::AddObject(string _Name, Vec2 _Pos, float _Z, float _Depth, ObjectTag _Tag)
{
	cObject* a = new cObject;
	a->m_Name = _Name;
	a->m_Pos = _Pos;
	a->m_Z = _Z;
	a->m_Depth = _Depth;
	a->m_Tag = _Tag;
	m_Objects[_Tag].push_back(a);
	return a;
}

void cObjectManager::CheckCollision(cObject * _Object)
{
	cCollider* Self = _Object->GC(cCollider);
	if (Self == nullptr || Self->m_Enable == false)
		return;
	cCollider* Other = nullptr;
	RECT Rect;

	for (auto& Tag : Self->m_CollWith)
	{
		for (auto& iter : m_Objects[Tag])
		{
			Other = iter->GC(cCollider);
			if (Other == nullptr || Other->m_Enable == false)
				continue;
			if (IntersectRect(&Rect, &Self->m_Rect, &Other->m_Rect))
			{
				for (auto& Comp : _Object->m_Components)
				{
					Comp->OnCollision(iter, Rect);
				}
			}
		}
	}
}
