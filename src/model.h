//
// Created by PUNO_ on 12/4/18.
//

#pragma once

#include <ge211.h>
#include <vector>

using namespace std;
using namespace ge211;

struct tree_obstacles_
{
    Position pos;
    unsigned int tree_size_;
    unsigned int gap_;
    tree_obstacles_(Position pos, unsigned int size, unsigned int gap)
        : pos(pos), tree_size_(size), gap_(gap) {}
};

class Model
{
  public:
    explicit Model(Position pos = {0, 24});

    void start_running();

    /// control the dinosaur to move(jump) when key down
    void jump();

    void end_jump();

    void update(double);

    void updateJump(double);

    /// to check whether it hitting a ground obstacle, a coin or a flying obstacle
    bool is_hitted() const;

    bool is_started() const;

    void game_over();

    /// key: enter for restart
    void start_over();

    bool is_jumping() const;

    void setSpeedDrop(bool);

    bool checkForCollision() const;

    void increaseAll(double);

    vector<tree_obstacles_> ground_obstacles() const
    {
        return ground_obstacles_;
    };

    vector<Position> flying_obstacles() const
    {
        return flying_obstacles_;
    };

    vector<Position> coins() const
    {
        return coins_;
    };

    Position dino() const
    {
        return dino_;
    }

    bool is_game_over;

    void set_hitted(bool);

    bool boxcompare(vector<int>, vector<int>) const;

    double get_speed() const { return speed_; }

  private:
    //dimension width
    int WIDTH = 600;

    int TREE_WIDTH = 25;

    int FPS = 60;

    ///the number of coins dinosaur got
    size_t coin_num_;

    //the running distance dinosaur reached
    double running_distance_;

    ///game speed for now
    double speed_;

    double gap_coefficient_ = 0.6;

    double MAX_SPEED = 13.0;

    unsigned int MAX_OBSTACLE_LENGTH = 3;

    double INIITAL_JUMP_VELOCITY = -10.0;

    double DROP_VELOCITY_ = -3.0;

    double SPEED_DROP_COEFFICIENT = 10.0;

    double GRAVITY = 1;

    double ACCELERATION = 0.001;

    double MAX_GAP_COEFFICIENT = 1.5;

    ///jump velocity
    double jump_velocity_;

    int MIN_JUMP_HEIGHT = 50;
    int MAX_JUMP_HEIGHT = 50;

    Duration dur_;

    /// ms
    double running_time_;

    bool jumping;
    bool hitted;
    bool started;
    bool speedDrop;
    bool reached_min_height;

    /// The obstacles' position:
    vector<tree_obstacles_> ground_obstacles_;
    vector<Position> flying_obstacles_;

    /// The dinosaur's position:
    Position dino_;

    /// The coins' position:
    vector<Position> coins_;

    unsigned int getRandomNumber(unsigned int, unsigned int);

    void updateObstacles(double);

    /// generate obstacles according to current speed;
    void addNewTreeObstacle();

    unsigned int getGap(unsigned int);

    void add_new_coins_();

    bool boxcompare_(vector<int>, vector<int>) const;

    void setSpeed(double speed);

    void anim_ground_obs_per_frame(double);

    ///generate dinosaur pos when it start a jump
    /// near the top and come back down

    void anim_flyingobs_();

    bool hit_flyingob() const;

    bool hit_coin() const;

    void reset();

    void cleanVectors();
};
