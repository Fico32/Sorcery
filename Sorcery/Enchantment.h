#ifndef _ENCHANTMENT_H_
#define _ENCHANTMENT_H_
#include <memory>
#include "Card.h"

class Enchantment: public Card{
		//shared_ptr<Enchantment> otherEnchantments;
	public:
		Enchantment(string name);
		bool playCard(int which, int i, Player & self, Player & other);
};
#endif
