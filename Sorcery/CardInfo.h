#ifndef _CARDINFO_H_
#define _CARDINFO_H_
#include <vector>
#include <memory>
#include <string>

using namespace std;

//if an int is -1 then it is thought of as not existing only card types that use these values will change them from -1
struct CardInfo{
	string name;
	int cost;
	string type;
	string description; //stores description of spell/ activatedAbility/TriggeredAbility ... depending on which card. Empty string if not necessary
	int attack = -1;
	int defence = -1;
	string enchantMethod = ""; //Empty string or mult or add
	int activationCost = -1;
	int remainingCharges = -1;
	CardInfo(string n, int c, string t, string d):name(n),cost(c),type(t),description(d){}
	CardInfo(){}
};
#endif
