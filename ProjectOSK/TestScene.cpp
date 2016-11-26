#include "TestScene.h"
#include "GameManager.h"
#include "Image.h"

using namespace BombBombCrash;

TestScene::TestScene():
gameManager(std::make_shared<GameManager>())
{
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
	Image::GetInstance()->Initialize();
	gameManager->Initialize();
}

void TestScene::Finalize()
{
	gameManager->Finalize();
	Image::GetInstance()->Finalize();
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


