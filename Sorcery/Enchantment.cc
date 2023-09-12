#include "Enchantment.h"
#include "Player.h"
#include "Hand.h"
#include "Deck.h"
#include <memory>

using namespace std;

Enchantment::Enchantment(string name):Card(name){
	
}

bool Enchantment::playCard(int which, int i, Player & self, Player & other){
	Player & chosen = other;
	if(which == 0){
		chosen = self;
	}
	shared_ptr<Enchantment> ench = make_shared<Enchantment>(*this);
	return chosen.onBoard->attachEnchant(i, ench);
}
