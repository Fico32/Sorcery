#ifndef _GIANTSTRENGTH_H_
#define _GIANTSTRENGTH_H_
#include <memory>
#include "Card.h"

class GiantStrength: public Enchantment{
	public:
		GiantStrength(string name);
		void enchant() override;
};
#endif
