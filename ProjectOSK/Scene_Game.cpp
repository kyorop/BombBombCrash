#include "Scene_Game.h"
#include "Image.h"
#include "GameManager.h"

using namespace BombBombCrash;

Scene_Game::Scene_Game()
{

}


Scene_Game::~Scene_Game(void)
{
}


void Scene_Game::UpdateScene()
{

}


void Scene_Game::Initialize()
{
	Image::GetInstance()->Initialize();
	GameManager::Instance().Initialize();
}


void Scene_Game::Finalize()
{
	GameManager::Instance().Finalize();
	Image::GetInstance()->Finalize();
}


void Scene_Game::Update()
{
	GameManager::Instance().Update();
	UpdateScene();
}


void Scene_Game::Draw()
{
	GameManager::Instance().Draw();
}