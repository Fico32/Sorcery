#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <memory>
#include <string>
#include <vector>

class Hand;
class Deck;
class TextDisplay;

using namespace std;

class Player{
		int whichPlayer;
		int magic = 3;
		int life = 20;
		string name;
		shared_ptr<Deck> playerDeck;
		shared_ptr<Hand> inHand;// make private after
	public:
		int getHandSize();
		shared_ptr<Hand> onBoard;
		vector<int> triggers;
		vector<string> minionTriggers;
		Player(int w, string n, shared_ptr<Deck> d);
		int getWhichPlayer(){return whichPlayer;}
		string getName(){return name;}
		void updateState();
		void handNotify();
		void discard(int index);
		void deckToHand();
		void boardToHand(int i);
		bool playCard(int whichAttack, int index, int indexT, shared_ptr<Player> other);
		void useMinion(int whichAttack, int index, int indexT, Player & other);
		void summonAir(int i);
		int getMagic(){ return magic; }
		void setMagic(int m){magic = m;}
		int getLife(){ return life; }
		void setLife(int l){life = l;}
		void attach(shared_ptr<TextDisplay> ob);
};

#endif
