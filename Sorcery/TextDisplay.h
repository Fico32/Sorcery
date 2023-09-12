#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include "Observer.h"
#include "vector"
#include "Card.h"
#include "Hand.h"

template <typename StateType> class Subject;


class TextDisplay: public Observer<HandState>{
		pair<CardInfo, CardInfo> graveyards;
		pair<vector<CardInfo>, vector<CardInfo>> minions;
		pair<CardInfo, CardInfo> rituals;
		pair<vector<CardInfo>,vector<CardInfo>> hands;
		void drawCard(CardInfo & ci, bool inspect = false);
	public:
		void notify(Subject<HandState> &whoFrom) override;
		void showBoard(shared_ptr<Player> cur, shared_ptr<Player> other);
		void inspect(int i, int p);
		void showHand(int p);
		void printCard(vector<string> v);
		vector<string> printPlayer(int player_num, std::string name,int life,int mana);
		void printCards(vector<vector<string>> v);
		vector<string> drawCardDelayed(CardInfo & ci);
};

#endif
