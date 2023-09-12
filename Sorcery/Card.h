#ifndef _CARD_H_
#define _CARD_H_
#include <map>
#include <string>
#include <memory>

struct CardInfo;
class Deck;
class Player;

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
	shared_ptr<CardInfo> enchants = nullptr;
	CardInfo(string n, int c, string t, string d):name(n),cost(c),type(t),description(d){}
	CardInfo(){}
};


class Card{
		//std::shared_ptr<Card> selectCard(Deck & deck);
	protected:
		CardInfo info;
	public:
		static map<string, CardInfo> defaults;
		static shared_ptr<Card> makeCard(string name);
		Card(string name);
		CardInfo getInfo();
		void boneGolem();
		virtual bool playCard(int which, int i, Player & self, Player & other) = 0;
};
#endif
