#include "Hand.h"
#include "Card.h"
#include "Deck.h"
#include "Ritual.h"
#include "Minion.h"
#include "Enchantment.h"
#include <iostream>

/*Hand::Hand(int p, bool b, shared_ptr<Deck> m, shared_ptr<Deck> g, shared_ptr<Ritual> r):main(m), graveyard(g){
	ritual.swap(r);
	std::vector<CardInfo> mainInfo;
	for(int i = 0; i < main->getSize(); ++i){
		mainInfo.push_back(main->peakCard(i)->getInfo());
	}
	state = HandState{p % 2, b, mainInfo, graveyard->drawCard(false)->getInfo(), ritual->getInfo()};
}*/

int Hand::getSizeMain(){return main->getSize();}
int Hand::getSizeYard(){return graveyard->getSize();}

void Hand::updateState(){
	if(graveyard->drawCard(false) != nullptr){
		state.graveInfo = graveyard->drawCard(false)->getInfo();
	}
	if(ritual != nullptr){
		state.ritualInfo = ritual->getInfo();
	}
	std::vector<CardInfo> mainInfo;
	for(int i = 0; i < main->getSize(); ++i){
		if(main->peakCard(i) != nullptr)
			mainInfo.push_back(main->peakCard(i)->getInfo());
	}
	state.mainInfos = mainInfo;
}

Hand::Hand(int p, bool b){
	main = make_shared<Deck>(Deck());
	graveyard = make_shared<Deck>(Deck());
	state = HandState{p % 2, b};
}

shared_ptr<Card> Hand::playFromMain(int whichAttack, int index, int indexT, Player & self, Player & other){
	return main->playCard(whichAttack, index, indexT, self, other);
}

void Hand::print(){
	for(int i = 0; i < main->getSize(); ++i){
		cout << main->peakCard(i)->getInfo().name << endl;
	}
	if(ritual != nullptr)
		cout << ritual->getInfo().name << endl;
	if(graveyard->getSize() > 0)
		cout << graveyard->peakCard(graveyard->getSize()-1)->getInfo().name << endl;
}

shared_ptr<Card> Hand::minionFromMain(int whichAttack, int index, int indexT, Player & self, Player & other){
	return main->useMinion(whichAttack, index, indexT, self, other);
}

shared_ptr<Card> Hand::mainOut(int index){
	return main->moveCard(index);
}

bool Hand::mainFull(){
		return (5 == main->getSize());
}

bool Hand::setRitual(shared_ptr<Card> r, Player & p){
	shared_ptr<Ritual> newR = dynamic_pointer_cast<Ritual>(r);
	if(newR == nullptr){
		cerr << "This is not good" << endl;
		return false;
	}
	if(ritual != nullptr)
		ritual->removeTrigger(p);
	ritual.swap(newR);
	return true;
}

void Hand::resetRitual(){
	ritual.reset();
}

bool Hand::ritualIsEmpty(){
	return (ritual == nullptr);
}

bool Hand::plusRitualCharges(int i){
	if(ritualIsEmpty()){
		cout << "There is no ritual" << endl;
		return false;
	}
	ritual->increaseCharges(i);
	return true;
}

bool Hand::deleteEnchantment(int i){
	if(main->peakCard(i) == nullptr){
		return false;
	}
	shared_ptr<Minion> minion = dynamic_pointer_cast<Minion>(main->peakCard(i));
	if(minion == nullptr){
		cerr << main->peakCard(i)->getInfo().name << endl;
		return false;
	}
	return minion->deleteEnchantment(i);
}

bool Hand::trigerredAbility(){
	if(ritualIsEmpty()){
		cerr << "This is not supposed to happen";
	}
	return ritual->trigerredAbility();
}

void Hand::refreshMinions(){
	for(int i = 0; i < main->getSize(); ++i){
		shared_ptr<Minion> minion = dynamic_pointer_cast<Minion>(main->peakCard(i));
		minion->resetEnergy();
	}
}

bool Hand::graveToMain(){
	if(5 > main->getSize())
		main->push(graveyard->drawCard());
	else{
		cout << "You already have 5 active minions" << endl;
		return false;
	}
	return true;
}

bool Hand::checkDeath(int index){
	bool b = (main->peakCard(index)->getInfo().defence <= 0);
	if(b){
		mainToGrave(index);
	}
	return b;
}

bool Hand::mainToGrave(int index){
	if(index < main->getSize()){
		shared_ptr<Minion> minion = dynamic_pointer_cast<Minion>(main->moveCard(index));
		if(minion == nullptr){
			return false;
		}
		minion->killMinion();
		graveyard->push(minion);
	}
	else{
		cerr << "Should not be here" << endl;
		return false;
	}
	return true;
}

void Hand::boneGolem(){
	for(int i = 0; i < main->getSize(); ++i){
		if(main->peakCard(i)->getInfo().name == "Bone Golem"){
			main->peakCard(i)->boneGolem();
		}
	}
}

bool Hand::dmgMinion(int i, int d){	
	if(i < main->getSize())
		main->dmgMinion(i,d);
	else{
		cout << "This is not a valid card choice" << endl;
		return false;
	}
	return true;
}

bool Hand::mainPush(shared_ptr<Card> c, bool over){
	if(main->getSize() < 5 || over)
		main->push(c);
	else{
		cout << "You already have 5 active minions" << endl;
		return false;
	}
	return true;
}

bool Hand::attachEnchant(int i, shared_ptr<Enchantment> ench){
	if(main->peakCard(i) == nullptr){
		return false;
	}
	shared_ptr<Minion> minion = dynamic_pointer_cast<Minion>(main->peakCard(i));
	if(minion != nullptr)
		minion->addEnchantment(ench);
	else
		cerr << main->peakCard(i)->getInfo().name << endl;
}

int Hand::getAttack(int indexT){
	return main->peakCard(indexT)->getInfo().attack;
}

//void Hand::graveyardPush(Card & c){
//	graveyard.push(c);
//}


