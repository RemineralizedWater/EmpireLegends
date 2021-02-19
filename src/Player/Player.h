#ifndef EMPIRELEGENDS_PLAYER_H
#define EMPIRELEGENDS_PLAYER_H

#include <string>
#include <iostream>
#include <memory>
#include "../BiddingFacility/BiddingFacility.h"


class Player {
public:

    Player(const Player &playerToCopy);

    Player(const std::string &region);

    Player &operator=(const Player &playerToCopy);

    void PayCoin();

    void PlaceNewArmies();

    void MoveArmies();

    void MoveOverLand();

    void BuildCity();

    void DestroyArmy();

    friend std::istream &operator>>(std::istream &is, Player &player);

private:
    //just one attribute added for stream insertion operator
    std::unique_ptr<std::string> region_;
    unique_ptr<BiddingFacility> biddingFacility;
    //TODO add regions/countries
    //TODO add hand of cards meaning cards class

};

std::istream &operator>>(std::istream &is, Player &player);

#endif //EMPIRELEGENDS_PLAYER_H
