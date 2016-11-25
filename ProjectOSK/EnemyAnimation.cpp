#include "EnemyAnimation.h"
#include "Image.h"
#include "Enemy.h"

using namespace BombBombCrash;

EnemyAnimation::EnemyAnimation(const Enemy& enemy) :
enemy(enemy),
image_left(BombBombCrash::Image::GetInstance()->GetCharacterImage(enemy.Id(), Image::LEFT)),
image_right(Image::GetInstance()->GetCharacterImage(enemy.Id(), Image::RIGHT)),
image_up(Image::GetInstance()->GetCharacterImage(enemy.Id(), Image::UP)),
image_down(Image::GetInstance()->GetCharacterImage(enemy.Id(), Image::DOWN)),
image_death(Image::GetInstance()->GetCharacterImage(enemy.Id(), Image::DEATH))
{
}
