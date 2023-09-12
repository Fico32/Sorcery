#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include "Hand.h"
#include "TextDisplay.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void initializeCards(){
		CardInfo cur = CardInfo("Air Elemental", 0, "Minion", "");
		cur.attack = 1;
		cur.defence = 1;
		Card::defaults["Air Elemental"] = cur;
		cur = CardInfo("Earth Elemental", 3, "Minion", "");
		cur.attack = 4;
		cur.defence = 4;
		Card::defaults["Earth Elemental"] = cur;
		cur = CardInfo("Fire Elemental", 2, "Minion", "Whenever an opponents minion enters play, deal 1 damage to it");
		cur.attack = 2;
		cur.defence = 2;
		Card::defaults["Fire Elemental"] = cur;
		cur = CardInfo("Bone Golem", 2, "Minion", "Gain +1/+1 whenever a minion leaves play");
		cur.attack = 1;
		cur.defence = 3;
		Card::defaults["Bone Golem"] = cur;
		cur = CardInfo("Potion Seller", 2, "Minion", "At the end of your turn, all your minions gain +0/+1");
		cur.attack = 1;
		cur.defence = 3;
		Card::defaults["Potion Seller"] = cur;
		cur = CardInfo("Novice Pyromancer", 1, "Minion", "Deal one damage to target minion");
		cur.activationCost = 1;
		cur.attack = 0;
		cur.defence = 1;
		Card::defaults["Novice Pyromancer"] = cur;
		cur = CardInfo("Apprentice Summoner", 1, "Minion", "Summon a 1/1 air elemental");
		cur.activationCost = 1;
		cur.attack = 1;
		cur.defence = 1;
		Card::defaults["Apprentice Summoner"] = cur;
		cur = CardInfo("Master Summoner", 3, "Minion", "Summon up to 3 1/1 air elementals");
		cur.activationCost = 2;
		cur.attack = 2;
		cur.defence = 3;
		Card::defaults["Master Summoner"] = cur;
		cur = CardInfo("Banish", 2, "Spell", "Destroy target minion or ritual");
		Card::defaults["Banish"] = cur;
		cur = CardInfo("Unsummon", 1, "Spell", "Return target minion to its owner's hand");
		Card::defaults["Unsummon"] = cur;
		cur = CardInfo("Recharge", 1, "Spell", "Your ritual gains 3 charges");
		Card::defaults["Recharge"] = cur;
		cur = CardInfo("Disenchant", 1, "Spell", "Destroy the top enchantment on target minion");
		Card::defaults["Disenchant"] = cur;
		cur = CardInfo("Raise Dead", 1, "Spell", "Ressurect the top minion in your graveyard and set its defence to 1");
		Card::defaults["Raise Dead"] = cur;
		cur = CardInfo("Blizzard", 3, "Spell", "Deal 2 damage to all minions");
		Card::defaults["Blizzard"] = cur;
		cur = CardInfo("Giant Strength", 1, "Enchantment", "");
		cur.attack = 2;
		cur.defence = 2;
		cur.enchantMethod = "+";
		Card::defaults["Giant Strength"] = cur;
		cur = CardInfo("Enrage", 2, "Enchantment", "");
		cur.attack = 2;
		cur.defence = 2;
		cur.enchantMethod = "*";
		Card::defaults["Enrage"] = cur;
		cur = CardInfo("Haste", 1, "Enchantment", "Enchanted minions gain +1 action each turn");
		Card::defaults["Haste"] = cur;
		cur = CardInfo("Magic Fatigue", 0, "Enchantment", "Enchanted minion's activated ability costs 2 more");
		Card::defaults["Magic Fatigue"] = cur;
		cur = CardInfo("Silence", 1, "Enchantment", "Enchanted minion cannot use abilties");
		Card::defaults["Silence"] = cur;
		cur = CardInfo("Dark Ritual", 0, "Ritual", "At the start of oyur turn gain one magic");
		cur.activationCost = 1;
		cur.remainingCharges = 5;
		Card::defaults["Dark Ritual"] = cur;
		cur = CardInfo("Aura of Power", 1, "Ritual", "Whenever a minion enters play under your control, it gains +1/+1");
		cur.activationCost = 1;
		cur.remainingCharges = 4;
		Card::defaults["Aura of Power"] = cur;
		cur = CardInfo("Standstill", 3, "Ritual", "Whenever a minion enters play, destroy it");
		cur.activationCost = 2;
		cur.remainingCharges = 4;
		Card::defaults["Standstill"] = cur;
}

void printHelp(){
	cout << "Commands: help -- Display this message." << endl;
	cout << "end -- End the current player’s turn." << endl;
	cout << "quit -- End the game." << endl;
	cout << "attack minion other-minion -- Orders minion to attack other-minion." << endl;
	cout << "attack minion -- Orders minion to attack the opponent." << endl;
	cout << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
	cout << "use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player." << endl;
	cout << "inspect minion -- View a minion’s card and all enchantments on that minion." << endl;
	cout << "hand -- Describe all cards in your hand." << endl;
	cout << "board -- Describe all cards on the board." << endl;
}

int main(){
	bool testing = false;
	shared_ptr<TextDisplay> td = make_shared<TextDisplay>(TextDisplay());
	initializeCards();
	string name1;
	string name2;
	cout << "What is the name of the first player?" << endl;
	cin >> name1;
	cout << "What is the name of the second player?" << endl;
	cin >> name2;
	shared_ptr<Deck> deck1 = make_shared<Deck>("default.deck");
	shared_ptr<Deck> deck2 = make_shared<Deck>("default.deck");
	deck1->shuffle();
	deck2->shuffle();
	Player p1(1, name1, deck1);
	Player p2(2, name2, deck2);
	shared_ptr<Player> curPlayer = make_shared<Player>(p1);
	shared_ptr<Player> otherPlayer = make_shared<Player>(p2);
	curPlayer->onBoard->attach(td);
	otherPlayer->onBoard->attach(td);
	curPlayer->attach(td);
	otherPlayer->attach(td);
	getline(cin, name1);
	while(true){
		curPlayer->setMagic(1+curPlayer->getMagic());
		curPlayer->deckToHand();
		//Start of turn effects, this includs resseting the minions energy and scuh
		curPlayer->onBoard->refreshMinions();
		if(curPlayer->triggers[0] == 1 && curPlayer->onBoard->trigerredAbility()){
			curPlayer->setMagic(1+curPlayer->getMagic());
		}
		//td->showBoard();	
		string curMove;
		string line;
		int index;
		int indexT;
		curPlayer->onBoard->updateState();
		curPlayer->onBoard->notifyObservers();
		curPlayer->updateState();
		curPlayer->handNotify();
		otherPlayer->onBoard->updateState();
		otherPlayer->onBoard->notifyObservers();
		while(curMove != "end"){
			cout << curPlayer->getName() << "'s turn:" << endl;
			getline(cin, line);
			istringstream lineStream{line};
			lineStream >> curMove;
			
			if(curMove == "quit"){
				break;
			}
			else if(testing && curMove == "draw"){
				curPlayer->deckToHand();
			}
			else if(testing && curMove == "discard"){
				lineStream >> index; // check that this is indeed an int
				curPlayer->discard(index);
			}
			else if(curMove == "attack"){
				lineStream >> index; // check to make number;
				lineStream >> indexT;
				if(lineStream.fail()){
						indexT = -1;
				}
				curPlayer->useMinion(0,index, indexT, *otherPlayer);
			}
			else if(curMove == "use"){
				lineStream >> index; // check to make number;
				lineStream >> indexT;
				if(lineStream.fail()){
						indexT = -1;
				}
				curPlayer->useMinion(1,index, indexT, *otherPlayer);
			}
			else if(curMove == "play"){
				int p;
				lineStream >> index;
				lineStream >> p;
				lineStream >> indexT;
				if(lineStream.fail()){
					indexT = -1;
					p = -1;
				}
				curPlayer->playCard(p, index, indexT, otherPlayer);
			}
			else if(curMove == "inspect"){
				//lineStream >> index;
				td->inspect(index, curPlayer->getWhichPlayer() % 2);	
			}
			else if(curMove == "hand"){
				td->showHand(curPlayer->getWhichPlayer() % 2);
			}
			else if(curMove == "board"){
				td->showBoard(curPlayer, otherPlayer);
			}

			//Chewck if any minions died or players or maybe ritual idk if that spossiblwe
			if(curPlayer->getLife() <= 0 || otherPlayer->getLife() <= 0){
				break;
			}
			for(int i = 0; i < curPlayer->onBoard->getSizeMain(); ++i){
				if(curPlayer->onBoard->checkDeath(i)){
					curPlayer->onBoard->boneGolem();
					otherPlayer->onBoard->boneGolem();
				}
			}
			for(int i = 0; i < otherPlayer->onBoard->getSizeMain(); ++i){
				if(otherPlayer->onBoard->checkDeath(i)){
					curPlayer->onBoard->boneGolem();
					otherPlayer->onBoard->boneGolem();
				}
			}
			//update displays
			curPlayer->onBoard->updateState();
			curPlayer->onBoard->notifyObservers();
			curPlayer->updateState();
			curPlayer->handNotify();
			otherPlayer->onBoard->updateState();
			otherPlayer->onBoard->notifyObservers();
			
			//get new commands
			lineStream.clear();
		}
		if(curPlayer->getLife() <= 0 || otherPlayer->getLife() <= 0){
				break;
		}
		if(curMove == "quit"){
			break;
		}
		 
		//End of turn effects i literally hav eno idea what happens here
		for(int i = 0; i < curPlayer->minionTriggers.size(); ++i){
			if(curPlayer->minionTriggers[i] == "Potion Seller"){
				for(int j = 0; j < curPlayer->onBoard->getSizeMain(); ++j){
					curPlayer->onBoard->dmgMinion(j, -1);
				}
			}
		}
		//swap who is the active player
		curPlayer.swap(otherPlayer);
	}
	if(curPlayer->getLife() <= 0){
		cout << "Player " << otherPlayer->getWhichPlayer() << " wins" << endl;
	}
	else if(otherPlayer->getLife() <= 0){
		cout << "Player " << curPlayer->getWhichPlayer() << " wins" << endl;
	}
}
