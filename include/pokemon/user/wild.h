#ifndef WILD_H
#define WILD_H

#include <memory>

class Pokemon;

class Wild {
  public:
    std::shared_ptr<Pokemon> pokemon;

    Wild(std::shared_ptr<Pokemon> p);
    Wild() = default;
};

#endif
