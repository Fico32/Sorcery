#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "Observer.h"
#include<memory>
// TAKEN FROM A4Q3 - NOT MY CODE

using namespace std;

template <typename StateType> class Subject {
  std::vector<shared_ptr<Observer<StateType>>> observers;
 protected:
  StateType state;
  void setState(StateType newS);
 public:
  void attach(shared_ptr<Observer<StateType>> o);  
  void notifyObservers();
  StateType getState() const;
};

template <typename StateType>
void Subject<StateType>::attach(shared_ptr<Observer<StateType>> o) {
  observers.emplace_back(o);
}

template <typename StateType>
void Subject<StateType>::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

template <typename StateType>
void Subject<StateType>::setState(StateType newS) { state = newS; }

template <typename StateType>
StateType Subject<StateType>::getState() const { return state; }
#endif
