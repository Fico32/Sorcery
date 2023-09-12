#ifndef _MINION_H_
#define _MINION_H_
#include <memory>
#include "Card.h"
#include <vector>
class Enchantment;

class Minion: public Card{
		int action = 0;
		int possibleAction = 1;
		int whichTrigger = 0;
		std::vector<shared_ptr<Enchantment>> enchantments;
		//void basicAttack();
		//void activatedAttack();
	public:
		Minion(string name);
		void resetEnergy();
		bool playCard(int which, int i, Player & self, Player & other) override; //When the card is played if it has a triggered ability it will toggle a flag for this trigger in the main function
		bool useCard(int whichAttack, int indexT, Player & self, Player & other);
		bool deleteEnchantment(int i);
		void killMinion();
		void takeDmg(int d);
		void addEnchantment(shared_ptr<Enchantment> ench);
};
#endif
