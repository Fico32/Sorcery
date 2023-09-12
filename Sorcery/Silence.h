#ifndef _SILENCE_H_
#define _SILENCE_H_
#include <memory>
#include "Card.h"

class Silence: public Enchantment{
	public:
		Silence(string name);
		void enchant() override;
};
#endif
