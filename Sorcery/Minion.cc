#include "Minion.h"
#include "Player.h"
#include "Hand.h"
#include "Deck.h"
#include "Enchantment.h"
#include <iostream>

using namespace std;

Minion::Minion(string name):Card(name){
	if(name == "Bone Golem"){
		whichTrigger = 0;
	}
	else if(name == "Fire Elemental"){
		whichTrigger = 1;
	}
	else if(name == "Potion Seller"){
		whichTrigger = 2;
	}
}

void Minion::resetEnergy(){
	possibleAction = 1;
	for(int i = 0; i < enchantments.size(); ++i){
		if(enchantments[i]->getInfo().name == "Haste"){
			++possibleAction;
		}
	}
}

void Minion::addEnchantment(shared_ptr<Enchantment> ench){
	enchantments.push_back(ench);
}

bool Minion::playCard(int which, int i, Player & self, Player & other){
	if(self.triggers[1] == 1 && self.onBoard->trigerredAbility()){
		++info.attack;
		++info.defence;
	}
	self.minionTriggers.push_back(info.name);//activate triggers if any and just return true  cuz this only gets called if there is space to play it
	return true;
}

bool Minion::useCard(int whichAttack, int indexT, Player & self, Player & other){
	if(possibleAction <= 0){
		cout << "This minion is out of actions for this turn" << endl;
		return false;
	}
	if(whichAttack == 0){
		//regular attack
		if(indexT == -1){
			other.setLife(other.getLife() - info.attack);
		}
		else{
			takeDmg(other.onBoard->getAttack(indexT));
			other.onBoard->dmgMinion(indexT, info.attack);
		}
	}
	else{
		//activatedAttack
		if(info.activationCost < 0){
			cout << "This minion does not have an activated ability" << endl;
			return false;
		}
		bool silenced = false;
		for(int i = 0; i < enchantments.size(); ++i){
			if(enchantments[i]->getInfo().name == "Silenced"){
				silenced = true;
			}
		}
		if(silenced){
			cout << "This minion is silenced" << endl;
			return false;
		}
		int difference = self.getMagic()-info.activationCost;
		for(int i = 0; i < enchantments.size(); ++i){
			if(enchantments[i]->getInfo().name == "Magic Fatigue"){
				difference -= 2;
			}
		}
		if(difference < 0){
				cout << "Not enough magic to do this" << endl;
				return false;	
		}
		if(info.name == "Novice Pyromancer"){
			other.onBoard->dmgMinion(indexT, 1);
		}
		else if(info.name == "Apprentice Summoner"){
			self.summonAir(1);
		}
		else if(info.name == "Master Summoner"){
			self.summonAir(3);
		}
		else{
			cout << "This minion does not have an activated ability" << endl;
			return false;
		}
		self.setMagic(difference);
	}
	--possibleAction;
	return true;
}

bool Minion::deleteEnchantment(int i){
	if(enchantments.size() == 0){
		cout << "There are no enchantments" << endl;
		return false;
	}
	enchantments.pop_back();
	return true;
}

void Minion::killMinion(){
	while(enchantments.size() > 0){
		deleteEnchantment(enchantments.size() - 1);
	}
	info.defence = 0;
}

void Minion::takeDmg(int d){
	info.defence -= d;
}
