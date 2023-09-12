#include "Card.h"
#include "Minion.h"
#include "Ritual.h"
#include "Spell.h"
#include "Enchantment.h"
//#include "Enrage.h"
//#include "GiantStrength.h"
//#include "Haste.h"
//#include "Silence.h"
//#include "MagicFatigue.h"

#include <iostream>

using namespace std;

map<string, CardInfo> Card::defaults = {};

Card::Card(string name){
	info = defaults[name];
}

CardInfo Card::getInfo(){
	return info;
}

void Card::boneGolem(){
	++info.attack;
	++info.defence;
}

shared_ptr<Card> Card::makeCard(string name){
	if(defaults[name].type == "Minion"){
		Minion m = Minion(name);
		return make_shared<Minion>(m);
	}
	else if(defaults[name].type == "Spell"){
		Spell m = Spell(name);
		return make_shared<Spell>(m);
	}
	else if(defaults[name].type == "Ritual"){
		Ritual m = Ritual(name);
		return make_shared<Ritual>(m);
	}
	else if(defaults[name].type == "Enchantment"){
		Enchantment m = Enchantment(name);
		return make_shared<Enchantment>(m);
		/*if(name == "Haste"){
			Haste m = Haste(name);
			return make_shared<Haste>(m);
		}
		else if(name == "Silence"){
			Silence m = Silence(name);
			return make_shared<Silence>(m);
		}
		else if(name == "MagicFatigue"){
			MagicFatigue m = MagicFatigue(name);
			return make_shared<MagicFatigue>(m);
		}
		else if(name == "GiantStrength"){
			GiantStrength m = GiantStrength(name);
			return make_shared<GiantStrength>(m);
		}
		else if(name == "Enrage"){
			Enrage m = Enrage(name);
			return make_shared<Enrage>(m);
		}*/
	}
	cerr << "should not be here" << endl;
}


/*std::unique_ptr<Card> selectCard(Hand & hand){
	int index;
	std::cout << "Select a card to apply the affect to, by typing in a number from 1 to " << hand.getSize() << ". Cards are numbered from left to right." << std::endl;
	cin >> index;
	return hand.deck[i];
}*/
