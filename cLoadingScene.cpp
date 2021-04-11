#include "DXUT.h"
#include "cLoadingScene.h"


cLoadingScene::cLoadingScene()
{
}


cLoadingScene::~cLoadingScene()
{
}

void cLoadingScene::Init()
{
	LoadImage("");
	LoadImage("Effect");
	LoadImage("UI");
	LoadImage("Background");
	LoadImage("Character/Kyo");
	LoadImage("Character/Kim");
	LoadImage("Character/Robert");
	LoadImage("Character/Ralf");
	LoadImage("Character/Duck");
	LoadImage("Character/Big");
	LoadImage("Character/Iori_Player");
	LoadImage("Character/Iori");
	LoadImage("Character/Rugal");

	LoadSound("");
	LoadSound("Kyo");
	LoadSound("Robert");
	LoadSound("Ralf");
	LoadSound("Duck");
	LoadSound("Big");
	LoadSound("Iori");
	LoadSound("Iori_Player");
	LoadSound("Rugal");
	LoadSound("Kim");
	LoadSound("Effect");

	SCENE->ChangeScene("TITLE");
}

void cLoadingScene::Update()
{
}

void cLoadingScene::Render()
{
}

void cLoadingScene::Release()
{
}

void cLoadingScene::LoadImage(string _Path)
{
	string Searching = "./Resource/Image/" + _Path + "/*.png";
	string Key = "";
	string CurAnim = "";
	string Temp = "";
	int Count = 0;
	int Text = 100;

	_finddata_t Find;
	long Handle = _findfirst(Searching.c_str(), &Find);

	do
	{
		Key = Find.name;
		for (int i = 0; i < 4; i++)
		{
			Key.pop_back();
		}
		Temp.assign(Key.c_str(), min(sizeof(char) * Text, Key.size()));
		if (Count != 0 && (Temp != CurAnim || abs((int)Key.size() - (int)CurAnim.size()) > 2))
		{
			Count = 0;
			IMAGE->AddAnimation(CurAnim);
			CurAnim = "";
		}
		if (Key.back() == '1' && CurAnim == "" && (Temp != CurAnim || abs((int)Key.size() - (int)CurAnim.size()) > 2))
		{
			CurAnim = Key;
			CurAnim.pop_back();
			Count = 1;
			Text = CurAnim.size();
		}
		if (Count != 0)
		{
			Count++;
		}
		IMAGE->AddImage(Key, "./Resource/Image/" + _Path + "/" + Find.name);
	} while (_findnext(Handle, &Find) != -1);
	if (Count != 0)
	{
		IMAGE->AddAnimation(CurAnim);
	}
	_findclose(Handle);
}

void cLoadingScene::LoadSound(string _Path)
{
	string Searching = "./Resource/Sound/" + _Path + "/*.wav";
	string Key;

	_finddata_t Find;
	long Handle = _findfirst(Searching.c_str(), &Find);

	do
	{
		Key = Find.name;
		for (int i = 0; i < 4; i++)
		{
			Key.pop_back();
		}
		SOUND->AddSound(Key, "./Resource/Sound/" + _Path + "/" + Find.name);
	} while (_findnext(Handle, &Find) != -1);
	_findclose(Handle);
}
