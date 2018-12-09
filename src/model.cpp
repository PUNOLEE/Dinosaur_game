//
// Created by PUNO_ on 12/4/18.
//

#include "model.h"
#include <iostream>
using namespace ge211;

Model::Model(Position pos)
    : dino_(pos), coin_num_(0), running_distance_(0), running_time_(0)
{
}

bool Model::is_hitted() const
{
    return hitted;
}

void Model::end_jump()
{

    if (reached_min_height &&
        jump_velocity_ < DROP_VELOCITY_)
    {
        jump_velocity_ = DROP_VELOCITY_;
    }
}

void Model::jump()
{

    if (!jumping)
    {
        jumping = true;
        jump_velocity_ = INIITAL_JUMP_VELOCITY - (speed_ / 10);
        reached_min_height = false;
        speedDrop = false;
    }
}

void Model::updateJump(double last_frame_seconds)
{

    double deltatime = last_frame_seconds * 1000;

    double msPerFrame = 1000 / FPS;

    double frameElapsed = deltatime / msPerFrame;

    if (speedDrop)
    {

        dino_.y -= lround(jump_velocity_ * SPEED_DROP_COEFFICIENT * frameElapsed);
    }
    else
    {

        dino_.y -= lround(jump_velocity_ * frameElapsed);
    }

    jump_velocity_ += GRAVITY * frameElapsed;

    if (dino_.y > 24 + MIN_JUMP_HEIGHT || speedDrop)
    {
        reached_min_height = true;
    }

    if (dino_.y > MAX_JUMP_HEIGHT || speedDrop)
    {
        end_jump();
    }

    if (dino_.y < 24)
    {
        reset();
    }

    update(last_frame_seconds);
}

void Model::start_running()
{
    is_game_over = false;
    started = true;
    jumping = false;
    coin_num_ = 0;
    running_time_ = 0;
    running_distance_ = 0;
    setSpeed(3.0);
}

void Model::start_over()
{
    dino_ = {0, 24};
    running_time_ = 0;
    running_distance_ = 0;
    hitted = false;
    started = true;
    is_game_over = false;
    is_start_over = true;
    setSpeed(3.0);
}

void Model::update(double last_frame_seconds)
{

    double deltatime = last_frame_seconds * 1000;

    running_time_ += deltatime;

    if (started)
    {

        if (dino_.x >= WIDTH - 47)
            game_over();

        if (jumping)
            dino_.x += lround((4.2 * 60 / 1000) * deltatime);
        else
            dino_.x += lround((speed_ * 12 / 1000) * deltatime);

        updateObstacles(deltatime);
    }
}

void Model::setSpeed(double speed)
{
    speed_ = speed;
}

bool Model::is_jumping() const
{
    return jumping;
}

void Model::updateObstacles(double deltatime)
{

    if (!ground_obstacles_.empty())
    {
        auto lastone = ground_obstacles_.at(ground_obstacles_.size() - 1);
        if ((lastone.pos.x + lastone.tree_size_ * TREE_WIDTH + lastone.gap_) < WIDTH)
        {
            addNewTreeObstacle();
        }
    }
    else
    {
        addNewTreeObstacle();
    }

    anim_ground_obs_per_frame(deltatime);
}

unsigned int Model::getRandomNumber(unsigned int min, unsigned int max)
{
    return (rand() % (max - min + 1)) + min;
}

unsigned int Model::getGap(unsigned int size)
{

    int minGap_i;

    switch (size)
    {
    case 1:
        minGap_i = 150;
        break;
    case 2:
        minGap_i = 150;
        break;
    case 3:
        minGap_i = 170;
        break;
    default:
        break;
    }

    auto minGap = lround(TREE_WIDTH * size * speed_ + minGap_i * gap_coefficient_);

    auto maxGap = lround(minGap * MAX_GAP_COEFFICIENT);

    return getRandomNumber(minGap, maxGap);
}

//void Model::add_new_coins_() {
//    unsigned int co = getRandomNumber(0,1);
//    Position pos(WIDTH-10,80);
//    if (co==1)
//        coins_.push_back(pos);
//
//}

void Model::anim_ground_obs_per_frame(double deltatime)
{

    for (auto itr = ground_obstacles_.begin(); itr != ground_obstacles_.end(); ++itr)
    {

        itr->pos.x -= lround((60 * 5.2 / 1000) * deltatime);
        if (itr != ground_obstacles_.end() && itr->pos.x <= 0)
            ground_obstacles_.erase(itr);
    }
}

void Model::setSpeedDrop(bool b)
{
    speedDrop = b;
    if (b)
        jump_velocity_ = 1.0;
}

void Model::game_over()
{
    is_game_over = true;
    is_start_over = false;
    cleanVectors();
    started = false;
    reset();
}

void Model::addNewTreeObstacle()
{
    //obstacle size
    unsigned int size = getRandomNumber(1, MAX_OBSTACLE_LENGTH);

    //obstacle width
    int width = size * TREE_WIDTH;
    int xPos = WIDTH - width;

    //obstacle gap
    unsigned int gap = getGap(size);

    Position pos(xPos, 25);
    tree_obstacles_ to = tree_obstacles_(pos, size, gap);
    ground_obstacles_.push_back(to);
}

bool Model::checkForCollision() const
{
    bool crashed = false;
    vector<int> dinobox = {dino_.x, dino_.y, 44, 47};

    for (auto g_ob : ground_obstacles_)
    {
        vector<int> obstaclebox = {
            g_ob.pos.x,
            g_ob.pos.y,
            (int)(TREE_WIDTH * g_ob.tree_size_),
            50};

        crashed = boxcompare_(dinobox, obstaclebox);
        if (crashed)
            break;
    }
    return crashed;
}

bool Model::boxcompare(vector<int> dinobox, vector<int> obbox) const
{
    bool crashed = false;
    int dinox = dinobox.at(0);
    int dinoy = dinobox.at(1);
    int dinowi = dinobox.at(2);
    int dinohe = dinobox.at(3);

    int obx = obbox.at(0);
    int oby = obbox.at(1);
    int obwi = obbox.at(2);
    int obhe = obbox.at(3);

    if (dinox < obx + obwi &&
        dinox + dinowi > obx &&
        dinoy < oby + obhe)
        crashed = true;
    return crashed;
}

bool Model::boxcompare_(vector<int> dinobox, vector<int> obbox) const
{
    bool crashed = false;
    int dinox = dinobox.at(0);
    int dinoy = dinobox.at(1);
    int dinowi = dinobox.at(2);
    int dinohe = dinobox.at(3);

    int obx = obbox.at(0);
    int oby = obbox.at(1);
    int obwi = obbox.at(2);
    int obhe = obbox.at(3);

    if (dinox < obx + obwi - 10 && dinox + dinowi - 10 > obx && dinoy < oby + obhe - 10)
    {
        crashed = true;
    }
    return crashed;
}

bool Model::is_started() const
{
    return started;
}

void Model::cleanVectors()
{
    ground_obstacles_.clear();
    coins_.clear();
    flying_obstacles_.clear();
}

void Model::reset()
{
    dino_.y = 24;
    jump_velocity_ = 0;
    jumping = false;
    speedDrop = false;
}

void Model::increaseAll(double last_frame_seconds)
{

    double deltatime = last_frame_seconds * 1000;

    double msP = 1000 / 12;
    running_distance_ += speed_ * deltatime / msP;

    if (speed_ < MAX_SPEED)
        setSpeed(speed_ + ACCELERATION);
}

void Model::set_hitted(bool b)
{
    hitted = b;
}
