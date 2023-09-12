#ifndef _HASTE_H_
#define _HASTE_H_
#include <memory>
#include "Card.h"

class Haste: public Enchantment{
	public:
		Haste(string name);
		void enchant() override;
};
#endif
