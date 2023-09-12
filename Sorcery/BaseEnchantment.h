#ifndef _BASEENCHANTMENT_H_
#define _BASEENCHANTMENT_H_
#include <memory>
#include "Card.h"

class BaseEnchantment: public Enchantment{
	public:
		BaseEnchantment(string name);
		void enchant() override;
};
#endif
