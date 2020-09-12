#ifndef DBPLAYER_H
#define DBPLAYER_H

#include "player.h"

Player *FetchPlayer(UID uid);
UID isPlayerRegistered(std::string username);

#endif
