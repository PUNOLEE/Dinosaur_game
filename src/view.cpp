//
// Created by PUNO_ on 12/4/18.
//

#include "view.h"
#include <iostream>
using namespace ge211;

View::View(Model const &model) : model_(model)
{
}

Dimensions View::screen_dimensions() const
{
    return {600, 200};
}

void View::draw(Sprite_set &sprites, bool onkeydown_) const
{

    sprites.add_sprite(ground, Position(0, 188));
    sprites.add_sprite(cloud, Position(30, 0));
    sprites.add_sprite(cloud, Position(150, 0));
    sprites.add_sprite(cloud, Position(300, 0));

    sprites.add_sprite(dino, {model_.dino().x, 196 - model_.dino().y * 2});

    for (auto itr : model_.ground_obstacles())
    {

        switch (itr.tree_size_)
        {
        case 1:
            sprites.add_sprite(one_ob, {itr.pos.x, 196 - itr.pos.y * 2});
            break;
        case 2:
            sprites.add_sprite(two_ob, {itr.pos.x, 196 - itr.pos.y * 2});
            break;
        case 3:
            sprites.add_sprite(three_ob, {itr.pos.x, 196 - itr.pos.y * 2});
            break;
        default:
            break;
        }
    }

    if (model_.is_game_over)
    {
        sprites.add_sprite(text_game_over, Position(200, 100));
        sprites.add_sprite(startover, Position(400, 100));
    }
    //    if (onkeydown_){
    //
    //    }
}
