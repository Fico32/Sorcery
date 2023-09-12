#ifndef _ENRAGE_H_
#define _ENRAGE_H_
#include <memory>
#include "Card.h"

class Enrage: public Enchantment{
	public:
		Enrage(string name);
		void enchant() override;
};
#endif
