#ifndef _HANDSTATE_H_
#define _HANDSTATE_H_
#include <vector>
#include <memory>

struct CardInfo;

struct HandState{
	std::vector<CardInfo>; mainInfos;
	CardInfo graveInfo;
	CardInfo ritualInfo;
};
#endif
