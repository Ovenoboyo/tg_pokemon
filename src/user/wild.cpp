#include "pokemon/user/wild.h"

class Pokemon;

Wild::Wild(std::shared_ptr<Pokemon> p) {
     this->pokemon = p; 
}