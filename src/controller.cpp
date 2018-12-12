//
// Created by PUNO_ on 12/4/18.
//

#include "controller.h"
#include <iostream>
using namespace ge211;

Controller::Controller(Position pos) : model_(pos), view_(model_)
{
}
string Controller::initial_window_title() const
{
    return "Dinosaur Game";
}

Dimensions Controller::initial_window_dimensions() const
{
    return view_.screen_dimensions();
}

void Controller::on_key_down(Key key)
{

    if (!model_.is_started() && key == Key::code(13))
    {

        model_.start_running();
    }

    if (model_.is_started() && !model_.is_hitted() && key == Key::code(' '))
    {

        if (!model_.is_jumping())
        {
            model_.jump();
        }
    }

    if (model_.is_started() && model_.is_hitted() && key == Key::code(13))
    {

        model_.start_over();
    }

    //    if (model_.is_started()&&!model_.is_hitted()){
    //
    //        if (model_.is_jumping())
    //            model_.setSpeedDrop(true);
    //
    //    }
}

void Controller::on_key_up(Key key)
{

    bool is_jump_key = key == Key::code(' ');

    if (is_jump_key)
    {

        model_.end_jump();
    }
    else if (model_.is_hitted())
    {

        model_.setSpeedDrop(false);

        if (key == Key::code(13))
        {
            model_.start_over();
        }
    }
}

void Controller::draw(Sprite_set &set)
{
    view_.draw(set);
}

void Controller::on_start()
{
    Abstract_game::background_color = Color::white();
}

void Controller::on_frame(double last_frame_seconds)
{

    if (model_.is_start_over)
    {
        model_.is_start_over = false;
    }

    dur_ += last_frame_seconds;

    if (model_.is_started())
    {

        if (model_.is_jumping())
        {
            model_.updateJump(last_frame_seconds);
        }

        if (!model_.checkForCollision())
        {

            model_.increaseAll(last_frame_seconds);
        }
        else
        {
            model_.set_hitted(true);
            model_.game_over();
        }
    }

    if (!model_.is_hitted() && model_.is_started())
        model_.update(last_frame_seconds);
}
