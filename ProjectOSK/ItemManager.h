#pragma once
#define ITEMNUM 30

class Item;
class Block;
class Player;
class Charactor;
class ItemManager
{
private:
	Item *item[ITEMNUM];

public:

	Item* GetFirstItemPointa();
	void SetItem(const Block &block);
	void Draw();
    int CheckHitCharactor(Charactor &charctor)const;
	int GetBombState()const;//FALSE�̃{���A�C�e������Ԃ�
	int GetFireState()const;//FALSE�̉ἨA�C�e������Ԃ�
	int GetSpeedState()const;//FALSE�̃X�s�[�h�A�C�e������Ԃ�
	ItemManager(void);
	~ItemManager(void);
};

