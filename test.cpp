//
// Created by PUNO_ on 12/4/18.
//

#include "model.h"
#include <catch.h>


TEST_CASE("Example test")
{
    Model dinogame;
    CHECK( dinogame.dino().x == 22 );
    CHECK( dinogame.dino().y == 24 );
    CHECK_FALSE( dinogame.is_started());
    CHECK(true);
}


TEST_CASE("animate dino")
{
    Model dinogame;
    
}