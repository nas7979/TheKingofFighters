#pragma once
#include "cSingleton.h"
class cRenderer;
struct Texture
{
	LPDIRECT3DTEXTURE9 Image;
	D3DXIMAGE_INFO Info;
};
class cImageManager : public cSingleton<cImageManager>
{
public:
	cImageManager();
	~cImageManager();

	void Init();
	void Update();
	void Render();
	void Release();
	void Begin();
	void End();
	void DrawFire();
	void OnLostDevice();
	void OnResetDevice();

	map<string, Texture*> m_Images;
	map<string, vector<Texture*>*> m_Animations;
	list<cRenderer*> m_Fire;
	LPDIRECT3DSURFACE9 m_FireSuf = nullptr;
	LPDIRECT3DTEXTURE9 m_FireTex = nullptr;
	LPD3DXEFFECT m_FireShader;
	LPD3DXEFFECT m_OutlineShader;
	LPD3DXSPRITE m_Sprite;
	LPD3DXFONT m_Font;
	Matrix m_Mat;
	RECT m_Rect;
	Vec2 m_Center;

	void AddImage(string _Key, string _Path);
	void AddAnimation(string _Key);
	Texture* Find(string _Key);
	vector<Texture*>* FindAnimation(string _Key);
	
	void Render(Texture* _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, D3DCOLOR _Color = 0xffffffff, bool _View = false);
	void CenterRender(Texture* _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, D3DCOLOR _Color = 0xffffffff, bool _View = false);
	void RenderRect(Texture* _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, RECT _Rect, D3DCOLOR _Color = 0xffffffff, bool _View = false);
	void CenterRenderRect(Texture* _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, RECT _Rect, D3DCOLOR _Color = 0xffffffff, bool _View = false);
	void RenderText(wstring _Text, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, D3DCOLOR _Color = 0xffffffff, bool _View = false);
	void CenterRenderText(wstring _Text, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, D3DCOLOR _Color = 0xffffffff, bool _View = false);
};

#define IMAGE cImageManager::GetInstance()