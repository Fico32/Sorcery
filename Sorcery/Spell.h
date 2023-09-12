#ifndef _SPELL_H_
#define _SPELL_H_
#include <memory>
#include "Card.h"

class Spell: public Card{
	public:
		Spell(string name);
		bool playCard(int which, int i, Player & self, Player & other) override;
};
#endif
