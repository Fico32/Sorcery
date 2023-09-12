#ifndef _MAGICFATIGUE_H_
#define _MAGICFATIGUE_H_
#include <memory>
#include "Card.h"

class MagicFatigue: public Enchantment{
	public:
		MagicFatigue(string name);
		void enchant() override;
};
#endif
