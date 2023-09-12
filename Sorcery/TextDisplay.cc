#include "TextDisplay.h"
#include "ascii_graphics.h"
#include "Player.h"
#include <iostream>

using namespace std;

void TextDisplay::notify(Subject<HandState> &whoFrom){
	HandState state = whoFrom.getState();
	vector<CardInfo> * v = &hands.first;
	if(state.board){
		CardInfo * g = &graveyards.first;
		CardInfo * r = &rituals.first;
		v = &minions.first;
		if(state.player == 0){
			v = &minions.second;
			g = &graveyards.second;
			r = &rituals.second;
		}
		*g = state.graveInfo;
		*r = state.ritualInfo;
	}
	else if(state.player == 0){
		v = &hands.second;
	}
	v->clear();
	for(int j = 0; j < state.mainInfos.size(); ++j)
		v->push_back(state.mainInfos[j]);
}

void TextDisplay::showBoard(shared_ptr<Player> cur, shared_ptr<Player> other){
	//draw board
	vector<vector<string>> layer;
	if(other->getWhichPlayer() == 2){
		if(graveyards.second.name != ""){
				layer.push_back(drawCardDelayed(graveyards.second));
		}
		else
			layer.push_back(CARD_TEMPLATE_EMPTY);
		layer.push_back(CARD_TEMPLATE_EMPTY);
		layer.push_back(printPlayer(2, other->getName(), other->getLife() , other->getMagic()));
		layer.push_back(CARD_TEMPLATE_EMPTY);
		if(rituals.second.name != ""){
				layer.push_back(drawCardDelayed(rituals.second));
		}
		else
			layer.push_back(CARD_TEMPLATE_EMPTY);
		printCards(layer);
		layer.clear();
		for(int i = 0; i < 5; ++i){
			if(i < minions.second.size()){
				layer.push_back(drawCardDelayed(minions.second[i]));
			}
			else{
				layer.push_back(CARD_TEMPLATE_EMPTY);
			}
		}
		printCards(layer);
		layer.clear();
		printCard(CENTRE_GRAPHIC);
		for(int i = 0; i < 5; ++i){
			if(i < minions.first.size()){
				layer.push_back(drawCardDelayed(minions.first[i]));
			}
			else{
				layer.push_back(CARD_TEMPLATE_EMPTY);
			}
		}
		printCards(layer);
		layer.clear();
		if(graveyards.first.name != ""){
				layer.push_back(drawCardDelayed(graveyards.first));
		}
		else
			layer.push_back(CARD_TEMPLATE_EMPTY);
		layer.push_back(CARD_TEMPLATE_EMPTY);
		layer.push_back(printPlayer(1, cur->getName(), cur->getLife() , cur->getMagic()));
		layer.push_back(CARD_TEMPLATE_EMPTY);
		if(rituals.first.name != ""){
				layer.push_back(drawCardDelayed(rituals.first));
		}
		else
			layer.push_back(CARD_TEMPLATE_EMPTY);
		printCards(layer);
		layer.clear();
	}
	else if(other->getWhichPlayer() == 1){
		if(graveyards.first.name != ""){
				layer.push_back(drawCardDelayed(graveyards.first));
		}
		else
			layer.push_back(CARD_TEMPLATE_EMPTY);
		layer.push_back(CARD_TEMPLATE_EMPTY);
		layer.push_back(printPlayer(2, other->getName(), other->getLife() , other->getMagic()));
		layer.push_back(CARD_TEMPLATE_EMPTY);
		if(rituals.first.name != ""){
				layer.push_back(drawCardDelayed(rituals.first));
		}
		else
			layer.push_back(CARD_TEMPLATE_EMPTY);
		printCards(layer);
		layer.clear();
		for(int i = 0; i < 5; ++i){
			if(i < minions.first.size()){
				layer.push_back(drawCardDelayed(minions.first[i]));
			}
			else{
				layer.push_back(CARD_TEMPLATE_EMPTY);
			}
		}
		printCards(layer);
		layer.clear();
		printCard(CENTRE_GRAPHIC);
		for(int i = 0; i < 5; ++i){
			if(i < minions.second.size()){
				layer.push_back(drawCardDelayed(minions.second[i]));
			}
			else{
				layer.push_back(CARD_TEMPLATE_EMPTY);
			}
		}
		printCards(layer);
		layer.clear();
		if(graveyards.second.name != ""){
				layer.push_back(drawCardDelayed(graveyards.second));
		}
		else
			layer.push_back(CARD_TEMPLATE_EMPTY);
		layer.push_back(CARD_TEMPLATE_EMPTY);
		layer.push_back(printPlayer(1, cur->getName(), cur->getLife() , cur->getMagic()));
		layer.push_back(CARD_TEMPLATE_EMPTY);
		if(rituals.second.name != ""){
				layer.push_back(drawCardDelayed(rituals.second));
		}
		else
			layer.push_back(CARD_TEMPLATE_EMPTY);
		printCards(layer);
		layer.clear();
		
	}
	
}

vector<string> TextDisplay::printPlayer(int player_num,std::string name,int life,int mana){
	return (display_player_card(player_num, name, life, mana));
}


void TextDisplay::inspect(int i, int p){
	vector<CardInfo> & v = minions.first;
	if(p == 0){
		v = minions.second;
	}
	drawCard(v[i], true);
}

void TextDisplay::showHand(int p){
	vector<CardInfo> * v = &hands.first;
	if(p == 0){
		v = &hands.second;
	}
	for(int j = 0; j < v->size(); ++j)
		drawCard((*v)[j]);
}

void TextDisplay::drawCard(CardInfo & ci, bool inspect){
	if(ci.attack != -1 && ci.description == "" && ci.activationCost == -1){
		printCard(display_minion_no_ability(ci.name, ci.cost, ci.attack, ci.defence));
		if(inspect && ci.enchants != nullptr)
			drawCard(*(ci.enchants), true);
	}
	else if(ci.type == "Minion" && ci.attack != -1 && ci.activationCost == -1){
		printCard(display_minion_triggered_ability(ci.name, ci.cost, ci.attack, ci.defence, ci.description));
		if(inspect && ci.enchants != nullptr)
			drawCard(*(ci.enchants), true);
	}
	else if(ci.attack != -1){
		printCard(display_minion_activated_ability(ci.name, ci.cost, ci.attack, ci.defence, ci.activationCost, ci.description));
		if(inspect && ci.enchants != nullptr)
			drawCard(*(ci.enchants), true);
	}
	else if(ci.activationCost != -1){
		printCard(display_ritual(ci.name, ci.cost, ci.activationCost, ci.description, ci.remainingCharges));
	}
	else if(ci.description != ""){
		printCard(display_spell(ci.name, ci.cost, ci.description));
	}
	else if(ci.attack != -1 && ci.activationCost == -1){
		printCard(display_enchantment_attack_defence(ci.name, ci.cost, ci.description, ci.enchantMethod + to_string(ci.attack), ci.enchantMethod + to_string(ci.defence)));
	}
	else if(ci.type == "Enchantment"){
		printCard(display_enchantment(ci.name, ci.cost, ci.description));
	}
}

vector<string> TextDisplay::drawCardDelayed(CardInfo & ci){
	if(ci.attack != -1 && ci.description == "" && ci.activationCost == -1){
		return display_minion_no_ability(ci.name, ci.cost, ci.attack, ci.defence);
	}
	else if(ci.type == "Minion" && ci.attack != -1 && ci.activationCost == -1){
		return (display_minion_triggered_ability(ci.name, ci.cost, ci.attack, ci.defence, ci.description));
	}
	else if(ci.attack != -1){
		return (display_minion_activated_ability(ci.name, ci.cost, ci.attack, ci.defence, ci.activationCost, ci.description));
	}
	else if(ci.activationCost != -1){
		return (display_ritual(ci.name, ci.cost, ci.activationCost, ci.description, ci.remainingCharges));
	}
	else if(ci.description != ""){
		return (display_spell(ci.name, ci.cost, ci.description));
	}
	else if(ci.attack != -1 && ci.activationCost == -1){
		return (display_enchantment_attack_defence(ci.name, ci.cost, ci.description, ci.enchantMethod + to_string(ci.attack), ci.enchantMethod + to_string(ci.defence)));
	}
	else if(ci.type == "Enchantment"){
		return (display_enchantment(ci.name, ci.cost, ci.description));
	}
}


void TextDisplay::printCard(vector<string> v){
	for(int i = 0; i < v.size(); ++i){
		cout << v[i] << endl;
	}
}

void TextDisplay::printCards(vector<vector<string>> v){
	for(int i = 0; i < v[0].size(); ++i){
		for(int j = 0; j < v.size(); ++j){
			cout << v[j][i];
		}
		cout << endl;
	}
}
