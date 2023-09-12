#ifndef _RITUAL_H_
#define _RITUAL_H_
#include <vector>
#include "Card.h"

class Ritual: public Card{
	int whichRitual = -1; //0 -> dark, 1-> Aura of Power, 2->Standstill
	public:
		Ritual(string name);
		void removeTrigger(Player & self);
		bool playCard(int which, int i, Player & self, Player & other) override;
		bool trigerredAbility();
		void increaseCharges(int i);
};
#endif
