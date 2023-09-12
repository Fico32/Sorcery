#ifndef _HAND_H_
#define _HAND_H_
#include <vector>
#include <memory>
#include "Subject.h"
#include "Card.h"

using namespace std;

class Deck;
class Ritual;
class Enchantment;

struct HandState{
	int player;// 0 is player 2, 1 is player 1
	bool board;
	std::vector<CardInfo> mainInfos;
	CardInfo graveInfo;
	CardInfo ritualInfo;
	HandState(int p, bool b):player(p),board(b){}
	HandState(int p, bool b, std::vector<CardInfo> m, CardInfo g, CardInfo r):player(p),board(b),mainInfos(m),graveInfo(g),ritualInfo(r){}
	HandState(){};
};

class Hand: public Subject<HandState>{
		shared_ptr<Deck> main;
		shared_ptr<Deck> graveyard;
		shared_ptr<Ritual> ritual;
	public:
		bool plusRitualCharges(int i); 
		bool ritualIsEmpty();
		void resetRitual();
		bool trigerredAbility();
		bool mainFull();
		int getSizeMain();
		int getSizeYard();
		shared_ptr<Card> playFromMain(int whichAttack, int index, int indexT, Player & self, Player & other);
		shared_ptr<Card> minionFromMain(int whichAttack, int index, int indexT, Player & self, Player & other);
		bool mainToGrave(int index);
		bool graveToMain();
		shared_ptr<Card> mainOut(int index);
		bool mainPush(shared_ptr<Card> c, bool over = true);
		bool deleteEnchantment(int i);
		bool dmgMinion(int i, int d);
		//void graveyardPush(Card & c);
		bool setRitual(shared_ptr<Card> r, Player & p);
		int getAttack(int indexT);
		bool attachEnchant(int i, shared_ptr<Enchantment> ench);
		void print();
		void updateState();
		void refreshMinions();
		bool checkDeath(int index);
		void boneGolem();
		Hand(int p, bool b);
		//Hand(int p, bool b, shared_ptr<Deck> m, shared_ptr<Deck> g, shared_ptr<Ritual> r);
		
};

#endif
