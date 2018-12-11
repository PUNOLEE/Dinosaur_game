//
// Created by PUNO_ on 12/4/18.
//

#include "model.h"
#include <catch.h>
#include <vector>

TEST_CASE("Example test")
{
    Model dinogame;
    CHECK(dinogame.dino().x == 0);
    CHECK(dinogame.dino().y == 24);
    CHECK(dinogame.running_dis() == 0);
    CHECK(dinogame.running_time() == 0);
    CHECK(dinogame.coin_num() == 0);
}

TEST_CASE("crashed or not")
{
    Model dinogame;

    vector<int> dinobox = {0, 24, 44, 47};
    vector<int> obstaclebox = {43, 25, 75, 50};
    CHECK(dinogame.boxcompare(dinobox, obstaclebox));

    vector<int> dinobox2 = {0, 52, 44, 47};
    vector<int> obstaclebox2 = {43, 25, 75, 50};
    CHECK(dinogame.boxcompare(dinobox2, obstaclebox2));

    vector<int> dinobox3 = {0, 74, 44, 47};
    vector<int> obstaclebox3 = {44, 25, 75, 50};
    CHECK_FALSE(dinogame.boxcompare(dinobox3, obstaclebox3));

    vector<int> dinobox4 = {78, 52, 44, 47};
    vector<int> obstaclebox4 = {43, 25, 75, 50};
    CHECK(dinogame.boxcompare(dinobox4, obstaclebox4));

    vector<int> dinobox5 = {118, 74, 44, 47};
    vector<int> obstaclebox5 = {43, 25, 75, 50};
    CHECK_FALSE(dinogame.boxcompare(dinobox5, obstaclebox5));

    vector<int> dinobox6 = {43, 75, 44, 47};
    vector<int> obstaclebox6 = {43, 25, 75, 50};
    CHECK_FALSE(dinogame.boxcompare(dinobox6, obstaclebox6));

    vector<int> dinobox7 = {118, 24, 44, 47};
    vector<int> obstaclebox7 = {43, 25, 75, 50};
    CHECK_FALSE(dinogame.boxcompare(dinobox7, obstaclebox7));
}

TEST_CASE("Hit coin")
{
    Model dinogame;
    dinogame.set_dino_pos(125, 80);
    tree_obstacles_ to = tree_obstacles_({100, 25}, 3, 400, true);
    CHECK(dinogame.is_hit_coin(to));
}