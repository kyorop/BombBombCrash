#include "TestScene.h"
#include "Drawing.h"
#include "Image.h"
#include "GameManager.h"

using namespace BombBombCrash;

TestScene::TestScene() :
player(std::make_shared<Player>(ln::Vector2(32,32), Player::KEYBORAD)),
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
	gameManager->AddElement(player);

	for (size_t i = 0; i < 10; i++)
	{
		player->IncrementBomb();
	}
}

void TestScene::Finalize()
{
	gameManager->Destroy();
	Image::GetInstance()->Finalize();
}

void TestScene::UpdateScene()
{
}

void TestScene::Update()
{
	player->Update();
	drawer->Update();
	gameManager->Update();
}

void TestScene::Draw()
{
	gameManager->Draw();
}


