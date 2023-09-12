#include "Ritual.h"
#include "Player.h"

Ritual::Ritual(string name):Card(name){
	if(name == "Dark Ritual"){
		this->whichRitual = 0;
	}
	else if(name == "Aura of Power"){
		this->whichRitual = 1;
	}
	else{
		this->whichRitual = 2;
	}
}

bool Ritual::playCard(int which, int i, Player & self, Player & other){
	self.triggers[whichRitual] = 1;
	return true;
}

void Ritual::removeTrigger(Player & self){
	self.triggers[whichRitual] = 0;
}

void Ritual::increaseCharges(int i){
	info.remainingCharges += i;
}

bool Ritual::trigerredAbility(){
	int difference = info.activationCost - info.remainingCharges;
	if(difference > 0){
		info.remainingCharges = difference;
		return true;
	}
	return false;
}
