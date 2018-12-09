//
// Created by PUNO_ on 12/4/18.
//

#include "view.h"
#include <iostream>
#include <iomanip>

using namespace ge211;

View::View(Model const &model) : model_(model)
{
}

Dimensions View::screen_dimensions() const
{
    return {800, 200};
}

void View::draw(Sprite_set &sprites, bool onkeydown_)
{

    rtsprite.reconfigure(Text_sprite::Builder(sans_).color(Color::medium_red())
                         << lround(model_.running_time()) << "ms");

    rdsprite.reconfigure(Text_sprite::Builder(sans_).color(Color::medium_red())
                         << lround(model_.running_dis()) << "m");

    sprites.add_sprite(rtsprite, {10, 10});

    sprites.add_sprite(rdsprite, {700, 10});

    sprites.add_sprite(ground, Position(0, 188));

    for (int i = 0; i < 6; i++)
    {
        sprites.add_sprite(cloud, Position(30 + 150 * i, 0));
    }

    sprites.add_sprite(dino, {model_.dino().x, 196 - model_.dino().y * 2});

    if (!model_.ground_obstacles().empty())
    {
        for (auto const &itr : model_.ground_obstacles())
        {

            switch (itr.tree_size_)
            {
            case 1:
                sprites.add_sprite(one_ob, {itr.pos.x, 146});
                break;
            case 2:
                sprites.add_sprite(two_ob, {itr.pos.x, 146});
                break;
            case 3:
                sprites.add_sprite(three_ob, {itr.pos.x, 146});
                break;
            default:
                break;
            }
        }
    }

    if (model_.is_game_over)
    {
        sprites.add_sprite(text_game_over, Position(300, 100));
        sprites.add_sprite(startover, Position(500, 100));
    }
    //    if (onkeydown_){
    //
    //    }
}
