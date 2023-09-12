#include "Spell.h"
#include "Player.h"
#include "Hand.h"
#include "Deck.h"
#include <iostream>

using namespace std;

Spell::Spell(string name):Card(name){}

bool Spell::playCard(int which, int i, Player & self, Player & other){
	Player & chosen = other;
	if(which == 0){
		chosen = self;
	}
	if(info.name == "Banish"){
		if(i < 6){
			if(i < chosen.onBoard->getSizeMain()){
				chosen.onBoard->dmgMinion(i,1000);
			}
			else{
				cout << "This is not a valid card choice" << endl;
				return false;
			}
		}
		else if(i == 6){
			if(chosen.onBoard->ritualIsEmpty()){
				cout << "This player does not have a ritual" << endl;
				return false;
			}
			for(int i = 0; i < 3; ++i){
				chosen.triggers[i] = 0;
				chosen.onBoard->resetRitual();
			}
		}
	}
	else if(info.name == "Unsummon"){
		if(i < chosen.onBoard->getSizeMain()){
				chosen.boardToHand(i);
		}
		else{
			cout << "This is not a valid card choice" << endl;
			return false;
		}
	}
	else if(info.name == "Recharge"){
		if(!self.onBoard->ritualIsEmpty()){
			self.onBoard->plusRitualCharges(3);
		}
		else{
			cout << "You don't have an active ritual" << endl;
			return false;
		}
	}
	else if(info.name == "Disenchant"){
		if(i < chosen.onBoard->getSizeMain()){
			if(!chosen.onBoard->deleteEnchantment(i)){
				cout << "This minion does not have enchantments on it" << endl;
				return false;
			}
		}
		else{
			cout << "This is not a valid card choice" << endl;
			return false;
		}
	}
	else if(info.name == "Raise Dead"){
		if(self.onBoard->getSizeYard() == 0){
			cout << "Your graveyard is empty" << endl;
		}
		else if(self.onBoard->getSizeMain() == 5){
			cout << "You already have 5 minions in play" << endl;
			return false;
		}
		else{
			self.onBoard->graveToMain();
		}
	}
	else if(info.name == "Blizzard"){
		for(int i = 0; i < self.onBoard->getSizeMain(); ++i){
			self.onBoard->dmgMinion(i, 2);
		}
		for(int i = 0; i < other.onBoard->getSizeMain(); ++i){
			other.onBoard->dmgMinion(i, 2);
		}
	}
	return true;
}
