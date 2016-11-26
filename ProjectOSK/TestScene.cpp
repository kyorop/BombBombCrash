#include "TestScene.h"
#include "GameManager.h"

using namespace BombBombCrash;

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
	gameManager->Initialize();
}

void TestScene::Finalize()
{
	gameManager->Finalize();
}

void TestScene::UpdateScene()
{
}

void TestScene::Update()
{
	gameManager->Update();
}

void TestScene::Draw()
{
	gameManager->Draw();
}


