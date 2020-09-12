#ifndef DBPLAYER_H
#define DBPLAYER_H

#include "pokemon/player.h"

Player *FetchPlayer(UID uid);
UID isPlayerRegistered(std::string username);

#endif
