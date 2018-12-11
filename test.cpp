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

TEST_CASE("Running")
{
    Model dinogame;
    dinogame.start_running();
    CHECK(dinogame.speed() == 3.0);
    dinogame.update(0.001);
    CHECK(dinogame.running_time() == 1.0);
    CHECK(dinogame.is_started());
    CHECK(dinogame.dino().x == 0);
    CHECK_FALSE(dinogame.ground_obstacles().empty());
    CHECK_FALSE(dinogame.flying_obstacles().empty());
    dinogame.increaseAll(0.001);
    CHECK(dinogame.running_dis() > 0);
    CHECK(dinogame.speed() == 3.0006);
}

TEST_CASE("Jumping")
{
    Model dinogame;
    dinogame.start_running();
    dinogame.jump();
    CHECK(dinogame.is_jumping());
    dinogame.updateJump(0.001);
    CHECK(dinogame.dino().y == 25);
    dinogame.updateJump(0.001);
    CHECK(dinogame.dino().y == 26);
    dinogame.updateJump(0.001);
    CHECK(dinogame.dino().y == 27);
    dinogame.updateJump(0.08);
    CHECK(dinogame.jump_velocity() == -3.0);
    CHECK(dinogame.is_jumping());
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

TEST_CASE("Increase the score")
{
    Model dinogame;
    dinogame.set_dino_pos(125, 80);
    tree_obstacles_ to = tree_obstacles_({100, 25}, 3, 400, true);
    dinogame.increaseCoin(to);
    CHECK(dinogame.coin_num() == 1);
    dinogame.set_dino_pos(100, 80);
    tree_obstacles_ to2 = tree_obstacles_({100, 25}, 1, 400, true);
    dinogame.increaseCoin(to2);
    CHECK(dinogame.coin_num() == 2);
    dinogame.set_dino_pos(115, 80);
    tree_obstacles_ to3 = tree_obstacles_({100, 25}, 2, 400, true);
    dinogame.increaseCoin(to3);
    CHECK(dinogame.coin_num() == 3);
}

TEST_CASE("Game over")
{
    Model dinogame;
    dinogame.game_over();
    CHECK(dinogame.is_game_over);
    CHECK_FALSE(dinogame.is_start_over);
    CHECK(dinogame.ground_obstacles().empty());
    CHECK(dinogame.flying_obstacles().empty());
    CHECK_FALSE(dinogame.is_started());
    CHECK(dinogame.dino().y == 24);
    CHECK_FALSE(dinogame.is_jumping());
}
