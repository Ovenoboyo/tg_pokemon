#ifndef DBPLAYER_H
#define DBPLAYER_H

#include "pokemon/user/player.h"
#include <string> // for string

Player *FetchPlayer(UID uid);
UID isPlayerRegistered(std::string username);

#endif
