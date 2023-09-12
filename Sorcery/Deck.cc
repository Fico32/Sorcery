#include "Deck.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "Card.h"
#include "Player.h"
#include "Minion.h"
#include <string>
#include <memory>
#include <utility>
#include <iostream>
using namespace std;

Deck::Deck(string filename){
	srand(time(0));
	ifstream myfile{filename};
	string name;
	while(getline(myfile, name)){
		deck.push_back(Card::makeCard(name));
	}
}

shared_ptr<Card> Deck::peakCard(int i){
	if(deck.size() <= i){
		return nullptr;
	}
	return deck[i];
}

shared_ptr<Card> Deck::moveCard(int index){
	for(int i = index; i < deck.size()-1; ++i){
		deck[i].swap(deck[i+1]);
	}
	shared_ptr<Card> temp;
	temp.swap(deck.back());
	deck.pop_back();
	return temp;
}

void Deck::push(shared_ptr<Card> c){
	deck.push_back(c);
}

shared_ptr<Card> Deck::playCard(int whichAttack, int index, int indexT, Player & self, Player & other){
	if(index >= deck.size()){
		return nullptr;
	}
	if(!deck[index]->playCard(whichAttack, indexT, self, other)){
		return nullptr;
	}
	return deck[index];
}

shared_ptr<Card> Deck::useMinion(int whichAttack, int index, int indexT, Player & self, Player & other){
	//have to dynamic case the card to a minioin otherwise u cannot call use Card
	shared_ptr<Minion> minion = dynamic_pointer_cast<Minion>(deck[index]);
	minion->useCard(whichAttack, indexT, self, other);
	return deck[index];
}

shared_ptr<Card> Deck::drawCard(bool dispose){
	shared_ptr<Card> card;
	if(deck.size() == 0){
		return nullptr;
	}
	if(dispose){
		card.swap(deck.back());
		deck.pop_back();
		return card;
	}
	return deck.back();
}
void Deck::shuffle(){
	for(int i = 0; i < deck.size(); ++i){
		int randomNum = rand() % deck.size();
		deck[i].swap(deck[randomNum]);
	}
}

void Deck::dmgMinion(int i, int d){
	shared_ptr<Minion> minion = dynamic_pointer_cast<Minion>(deck[i]);
	minion->takeDmg(d);//have to cast deck[i] to minioin
}

int Deck::getSize(){
	return deck.size();
}

