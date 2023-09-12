#ifndef _DECK_H_
#define _DECK_H_
#include <vector>
#include <memory>

class Card;
class Player;

using namespace std;

class Deck{
		std::vector<std::shared_ptr<Card>> deck;
	public:
		Deck(string filename);
		Deck(){}
		void push(shared_ptr<Card> c);
		shared_ptr<Card> moveCard(int index);
		shared_ptr<Card> playCard(int whichAttack, int index, int indexT, Player & self, Player & other);
		shared_ptr<Card> useMinion(int whichAttack, int index, int indexT, Player & self, Player & other);
		shared_ptr<Card> drawCard(bool dispose = true);
		shared_ptr<Card> peakCard(int index);
		void dmgMinion(int i, int d);
		void shuffle();
		int getSize();
};
#endif
