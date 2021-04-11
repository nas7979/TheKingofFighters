#include "DXUT.h"
#include "cMainGame.h"
#include "cLoadingScene.h"
#include "cStage1Scene.h"
#include "cResultScene.h"
#include "cTitleScene.h"
#include "cSelectScene.h"

cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
}

void cMainGame::Init()
{
	IMAGE->CreateInstance();
	SOUND->CreateInstance();
	SYSTEM->CreateInstance();
	OBJECT->CreateInstance();
	INPUT->CreateInstance();
	PART->CreateInstance();
	CAMERA->CreateInstance();
	SCHEDULE->CreateInstance();
	SCENE->CreateInstance();

	SCENE->AddScene("LOADING", new cLoadingScene);
	SCENE->AddScene("TITLE", new cTitleScene);
	SCENE->AddScene("STAGE1", new cStage1Scene);
	SCENE->AddScene("RESULT", new cResultScene);
	SCENE->AddScene("SELECT", new cSelectScene);

	SCENE->ChangeScene("LOADING");
}

void cMainGame::Update()
{
	INPUT->Update();
	SYSTEM->Update();
	SCENE->Update();
	OBJECT->Update();
	PART->Update();
	CAMERA->Update();
	SCHEDULE->Update();
	SOUND->Update();
}

void cMainGame::Render()
{
	IMAGE->Begin();

	CAMERA->Render();
	SCENE->Render();
	OBJECT->Render();
	PART->Render();
	SYSTEM->Render();

	IMAGE->End();

	IMAGE->DrawFire();
}

void cMainGame::Release()
{
	SOUND->ReleaseInstance();
	SYSTEM->ReleaseInstance();
	OBJECT->ReleaseInstance();
	INPUT->ReleaseInstance();
	PART->ReleaseInstance();
	CAMERA->ReleaseInstance();
	SCHEDULE->ReleaseInstance();
	SCENE->ReleaseInstance();
	IMAGE->ReleaseInstance();
}

void cMainGame::OnLostDevice()
{
	IMAGE->OnLostDevice();
}

void cMainGame::OnResetDevice()
{
	IMAGE->OnResetDevice();
}
