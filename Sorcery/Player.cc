#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include "Hand.h"
#include "TextDisplay.h"
#include <string>
#include <iostream>

using namespace std;

Player::Player(int w, string n, shared_ptr<Deck> d):whichPlayer(w),name(n),playerDeck(d){
	inHand = make_shared<Hand>(Hand(w % 2, false));
	onBoard = make_shared<Hand>(Hand(w % 2, true));
	triggers = vector<int>(3);
}


bool Player::playCard(int whichAttack, int index, int indexT, shared_ptr<Player> other){
	shared_ptr<Card> chosen = inHand->playFromMain(whichAttack, index, indexT, *this, *other);
	if(chosen == nullptr){
		cout << "There is no card at this location" << endl;
		return false;
	}
	string type = chosen->getInfo().type;
	if(type == "Minion"){
		bool returnVal = onBoard->mainPush(inHand->mainOut(index));
		if(triggers[2] == 1 && onBoard->trigerredAbility()){
			onBoard->mainToGrave(onBoard->getSizeMain()-1);
			onBoard->boneGolem();
			
		}
		if(other->triggers[2] == 1 && other->onBoard->trigerredAbility()){
			onBoard->mainToGrave(onBoard->getSizeMain()-1);
			onBoard->boneGolem();
		}
		for(int i = 0; i < other->minionTriggers.size(); ++i){
			if(other->minionTriggers[i] == "Fire Elemental"){
				onBoard->dmgMinion(onBoard->getSizeMain()-1, 1);
			}
		}
		return returnVal;
	}
	else if(type == "Ritual"){
		return onBoard->setRitual(inHand->mainOut(index), *this);
	}
	else{
		return inHand->mainToGrave(index);
	}
}

void Player::updateState(){
	inHand->updateState();
}

int Player::getHandSize(){return inHand->getSizeMain();}

void Player::handNotify(){
	inHand->notifyObservers();
}

void Player::attach(shared_ptr<TextDisplay> ob){inHand->attach(ob);}

void Player::summonAir(int i){
	for(int j = 0; j < i; ++j){
		if(onBoard->getSizeMain() == 5){
			break;
		}
		onBoard->mainPush(Card::makeCard("Air Elemental"));
	}
}

void Player::discard(int index){
	inHand->mainToGrave(index);
}

void Player::deckToHand(){
	if(playerDeck->getSize() != 0)
		inHand->mainPush(playerDeck->drawCard(), true);
	else
		cout << "Your deck is empty" << endl;
}

void Player::useMinion(int whichAttack, int index, int indexT, Player & other){
	onBoard->minionFromMain(whichAttack, index, indexT, *this, other);
}

void Player::boardToHand(int i){
	inHand->mainPush(onBoard->mainOut(i));
}
