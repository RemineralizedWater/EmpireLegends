#ifndef EMPIRELEGENDS_PLAYER_H
#define EMPIRELEGENDS_PLAYER_H

#include <string>
#include <iostream>
#include <memory>

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

};

std::istream &operator>>(std::istream &is, Player &player);

#endif //EMPIRELEGENDS_PLAYER_H
