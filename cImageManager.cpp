#include "DXUT.h"
#include "cImageManager.h"


cImageManager::cImageManager()
{
}


cImageManager::~cImageManager()
{
}

void cImageManager::Init()
{
	D3DXCreateSprite(g_Device, &m_Sprite);
	AddFontResourceA("./Resource/DungGeunMo.ttf");
	D3DXCreateFont(g_Device, 64, 0, 0, 1, 0, DEFAULT_CHARSET, 0, 0, 0, L"¹Î9", &m_Font);
	LPD3DXBUFFER Error;
	D3DXCreateEffectFromFileA(g_Device, "./FireShader.fx", nullptr, nullptr, D3DXSHADER_DEBUG, nullptr, &m_FireShader, &Error);
	D3DXCreateEffectFromFileA(g_Device, "./OutlineShader.fx", nullptr, nullptr, D3DXSHADER_DEBUG, nullptr, &m_OutlineShader, &Error);
}

void cImageManager::Update()
{
}

void cImageManager::Render()
{
}

void cImageManager::Release()
{
	for (auto& iter : m_Images)
	{
		iter.second->Image->Release();
		delete iter.second;
	}
	for (auto& iter : m_Animations)
	{
		delete iter.second;
	}
	m_FireShader->Release();
	m_OutlineShader->Release();
	m_Sprite->Release();
	m_Font->Release();
	m_FireSuf->Release();
	m_FireTex->Release();
	RemoveFontResourceA("./Resource/DungGeunMo.ttf");
}

void cImageManager::Begin()
{
	m_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
	g_Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DX_FILTER_NONE);
	g_Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DX_FILTER_NONE);
	g_Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DX_FILTER_NONE);
	CAMERA->Render();
}

void cImageManager::End()
{
	m_Sprite->End();
}

void cImageManager::DrawFire()
{
	m_FireShader->SetTexture((D3DXHANDLE)"FireTexture", m_FireTex);
	m_FireShader->SetInt((D3DXHANDLE)"Time", timeGetTime() * 0.03);

	UINT num = 0;
	m_FireShader->Begin(&num, 0);
	for (int i = 0; i < num; i++)
	{
		Begin();
		m_FireShader->BeginPass(i);

		for (auto& iter : m_Fire)
		{
			m_FireShader->SetInt((D3DXHANDLE)"Pallete", iter->m_Fire - 1);
			CenterRender(iter->m_Image, iter->m_Owner->m_Pos - Vec2(0, iter->m_Owner->m_Z), iter->m_Owner->m_Scale, iter->m_Owner->m_Rot, iter->m_Owner->m_Depth, iter->m_Color);
		}

		m_FireShader->EndPass();
		End();
	}
	m_FireShader->End();
}

void cImageManager::OnLostDevice()
{
	m_Sprite->OnLostDevice();
	m_FireShader->OnLostDevice();
	m_OutlineShader->OnLostDevice();
}

void cImageManager::OnResetDevice()
{
	m_Sprite->OnResetDevice();
	m_FireShader->OnResetDevice();
	m_OutlineShader->OnResetDevice();

	LPDIRECT3DSURFACE9 Original;
	D3DSURFACE_DESC Desc;
	g_Device->GetRenderTarget(0, &Original);
	Original->GetDesc(&Desc);
	g_Device->CreateTexture(Desc.Width, Desc.Height, 0, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_FireTex, nullptr);
	m_FireTex->GetSurfaceLevel(0, &m_FireSuf);
	Original->Release();
}

void cImageManager::AddImage(string _Key, string _Path)
{
	Texture* Tex = new Texture;
	if (D3DXCreateTextureFromFileExA(g_Device, _Path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_POINT, D3DX_FILTER_POINT, 0, &Tex->Info, 0, &Tex->Image) == S_OK)
	{
		m_Images.insert(make_pair(_Key, Tex));
		return;
	}
	delete Tex;
}

void cImageManager::AddAnimation(string _Key)
{
	vector<Texture*>* Vec = new vector<Texture*>;
	char Text[64];
	for (int i = 1; true; i++)
	{
		sprintf(Text, "%s%d", _Key.c_str(), i);
		auto Find = m_Images.find(Text);
		if (Find != m_Images.end())
		{
			Vec->push_back(Find._Ptr->_Myval.second);
		}
		else
		{
			break;
		}
	}
	m_Animations.insert(make_pair(_Key, Vec));
}

Texture * cImageManager::Find(string _Key)
{
	return m_Images[_Key];
}

vector<Texture*>* cImageManager::FindAnimation(string _Key)
{
	return m_Animations[_Key];
}

void cImageManager::Render(Texture * _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, D3DCOLOR _Color, bool _View)
{
	D3DXMatrixTransformation2D(&m_Mat, NULL, 0, &_Scale, NULL, D3DXToRadian(_Rot), &(_Pos));
	if (_View)m_Mat *= CAMERA->m_InversedMat;
	m_Mat._43 = _Depth;
	m_Sprite->SetTransform(&m_Mat);
	m_Sprite->Draw(_Image->Image, nullptr, nullptr, nullptr, _Color);
}

void cImageManager::CenterRender(Texture * _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, D3DCOLOR _Color, bool _View)
{
	m_Center = Vec2(_Image->Info.Width * 0.5f, _Image->Info.Height * 0.5f);
	D3DXMatrixTransformation2D(&m_Mat, &m_Center, 0, &_Scale, &m_Center, D3DXToRadian(_Rot), &(_Pos - m_Center));
	if (_View)m_Mat *= CAMERA->m_InversedMat;
	m_Mat._43 = _Depth;
	m_Sprite->SetTransform(&m_Mat);
	m_Sprite->Draw(_Image->Image, nullptr, nullptr, nullptr, _Color);
}

void cImageManager::RenderRect(Texture * _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, RECT _Rect, D3DCOLOR _Color, bool _View)
{
	D3DXMatrixTransformation2D(&m_Mat, NULL, 0, &_Scale, NULL, D3DXToRadian(_Rot), &(_Pos));
	if (_View)m_Mat *= CAMERA->m_InversedMat;
	m_Mat._43 = _Depth;
	m_Sprite->SetTransform(&m_Mat);
	m_Sprite->Draw(_Image->Image, &_Rect, nullptr, nullptr, _Color);
}

void cImageManager::CenterRenderRect(Texture * _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, RECT _Rect, D3DCOLOR _Color, bool _View)
{
	m_Center = Vec2(_Image->Info.Width * 0.5f, _Image->Info.Height * 0.5f);
	D3DXMatrixTransformation2D(&m_Mat, &m_Center, 0, &_Scale, &m_Center, D3DXToRadian(_Rot), &(_Pos - m_Center));
	if (_View)m_Mat *= CAMERA->m_InversedMat;
	m_Mat._43 = _Depth;
	m_Sprite->SetTransform(&m_Mat);
	m_Sprite->Draw(_Image->Image, &_Rect, nullptr, nullptr, _Color);
}

void cImageManager::RenderText(wstring _Text, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, D3DCOLOR _Color, bool _View)
{
	D3DXMatrixTransformation2D(&m_Mat, NULL, 0, &_Scale, NULL, D3DXToRadian(_Rot), &(_Pos));
	if (_View)m_Mat *= CAMERA->m_InversedMat;
	m_Mat._43 = _Depth;
	m_Sprite->SetTransform(&m_Mat);
	m_Font->DrawTextW(m_Sprite, _Text.c_str(), -1, NULL, DT_NOCLIP, _Color);
}

void cImageManager::CenterRenderText(wstring _Text, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, D3DCOLOR _Color, bool _View)
{
	m_Rect.left = m_Rect.top = 0;
	m_Font->DrawTextW(m_Sprite, _Text.c_str(), -1, &m_Rect, DT_CALCRECT, _Color);
	m_Center = Vec2((float)m_Rect.right * 0.5f, (float)m_Rect.bottom * 0.5f);
	D3DXMatrixTransformation2D(&m_Mat, &m_Center, 0, &_Scale, &m_Center, D3DXToRadian(_Rot), &(_Pos - m_Center));
	if (_View)m_Mat *= CAMERA->m_InversedMat;
	m_Mat._43 = _Depth;
	m_Sprite->SetTransform(&m_Mat);
	m_Font->DrawTextW(m_Sprite, _Text.c_str(), -1, NULL, DT_NOCLIP | DT_CENTER | DT_VCENTER, _Color);
}