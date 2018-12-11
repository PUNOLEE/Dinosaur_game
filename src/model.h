//
// Created by PUNO_ on 12/4/18.
//

#pragma once

#include <ge211.h>
#include <vector>

using namespace std;
using namespace ge211;

/// How we represent a single tree obstacle
struct tree_obstacles_
{
    Position pos;
    unsigned int tree_size_;
    unsigned int gap_;
    bool hascoin_;
    tree_obstacles_(Position pos, unsigned int size, unsigned int gap, bool hascoin)
        : pos(pos), tree_size_(size), gap_(gap), hascoin_(hascoin) {}
};

class Model
{
  public:
    explicit Model(Position pos = {0, 24});

    /// Start running this game
    void start_running();

    /// Control the dinosaur to move(jump) when key down
    void jump();

    /// Control the dinosaur to drop when it reaches the max height
    void end_jump();

    /// Update every frame in seconds, fps: 60
    /// Mainly update the positions of obstacles and the number of coins
    void update(double);

    /// Update the dinosaur position when it jumps
    /// Also needs to update obstacles and coins using `update()` function.
    void updateJump(double);

    /// Return whether hits the obstacles
    bool is_hitted() const;

    /// Return whether the game is started
    bool is_started() const;

    /// Return whether the game is over
    void game_over();

    /// Key: enter for restart
    /// Restart the game with
    /// Coins gained
    void start_over();

    /// Return whether dinosaur is jumping
    bool is_jumping() const;

    /// Set the drop speed
    void setSpeedDrop(bool);

    /// Check whether the dinosaur collide with obstacles
    bool checkForCollision();

    /// Increase the running distance and current speed
    void increaseAll(double);

    vector<tree_obstacles_> ground_obstacles() const
    {
        return ground_obstacles_;
    };

    vector<Position> flying_obstacles() const
    {
        return flying_obstacles_;
    };

    Position dino() const
    {
        return dino_;
    }

    bool is_game_over;

    bool is_start_over;

    /// Set status to be hitted
    void set_hitted(bool);

    /// Compare the dinosaur's position and current obstacle's position
    /// **PRECONDITIONS**:
    /// -- Two vectors should not be empty; /// Com
    bool boxcompare(vector<int>, vector<int>) const;

    /// Return whether the dinosaur hits the coin
    /// **PRECONDITIONS**:
    /// -tree_obstacles should exist
    bool is_hit_coin(tree_obstacles_) const;

    double running_dis() const { return running_distance_; };

    double running_time() const { return running_time_; };

    int coin_num() const { return coin_num_; };

    double speed() const { return speed_; }

    double jump_velocity() const { return jump_velocity_; };

    /// Set the dinosaur's position
    void set_dino_pos(int xPos, int yPos)
    {
        dino_.x = xPos;
        dino_.y = yPos;
    };

    /// Increase the number of coin
    void increaseCoin(tree_obstacles_ &);

  private:
    // Dimension width
    int WIDTH = 800;

    // A single tree width
    int TREE_WIDTH = 25;

    // Current frame per second
    int FPS = 60;

    // The number of coins dinosaur got
    int coin_num_;

    // The running distance dinosaur reached
    double running_distance_;

    // Game speed for now
    double speed_;

    // Gap coefficient to get a vaild gap
    double gap_coefficient_ = 1.2;

    // Max gap coefficient
    double MAX_GAP_COEFFICIENT = 1.5;

    // Max speed
    double MAX_SPEED = 13.0;

    // Max tree obstacle length
    unsigned int MAX_OBSTACLE_LENGTH = 3;

    // Initial jump velocity
    double INIITAL_JUMP_VELOCITY = -12.0;

    // Drop velocity
    double DROP_VELOCITY_ = -3.0;

    // Speed drop coefficient
    double SPEED_DROP_COEFFICIENT = 12.0;

    // Gravity
    double GRAVITY = 1;

    // Acceleration
    double ACCELERATION = 0.0006;

    //jump velocity
    double jump_velocity_;

    // Minimum jump height
    int MIN_JUMP_HEIGHT = 55;
    // Maximum jump height
    int MAX_JUMP_HEIGHT = 60;

    // Running time in ms
    double running_time_;

    bool jumping;
    bool hitted;
    bool started;
    bool speedDrop;
    bool reached_min_height;

    // The tree obstacles' position:
    vector<tree_obstacles_> ground_obstacles_;

    // The flying obstacles' position:
    vector<Position> flying_obstacles_;

    // The dinosaur's position:
    Position dino_;

    /// Get a random number between the minimum and maximum number
    unsigned int getRandomNumber(unsigned int, unsigned int);

    /// Update obstacles' position in a moment
    /// Add new obstacles if needed
    void updateObstacles(double);

    /// Generate new tree obstacles
    /// Get width using a random number in {1,3}
    /// Get gap and decide whether a tree obstacle has a coin
    void addNewTreeObstacle();

    /// Generate new flying obstacles
    void addNewFlyingObs();

    /// Get a random gap for the next tree obstacle
    unsigned int getGap(unsigned int);

    /// Decide whether a tree obstacle has a coin
    bool has_coin_();

    /// Compare the dinosaur's position and current obstacle's position
    /// **PRECONDITIONS**:
    /// -- Two vectors should not be empty
    bool boxcompare_(vector<int>, vector<int>) const;

    /// Set the current speed
    void setSpeed(double speed);

    /// Animate tree obstacles per frame
    void anim_ground_obs_per_frame(double);

    /// Animate flying obstacles per frame
    void anim_flying_obs_per_frame(double);

    /// Return whether the dinosaur hits the coin
    /// **PRECONDITIONS**:
    /// -tree_obstacles should exist
    bool is_hit_coin_(tree_obstacles_) const;

    /// Reset the jumping status to running status
    void reset();

    /// Increase the number of coins
    void increaseCoin_(tree_obstacles_ &);

    /// Clean all vectors when game starts over
    void cleanVectors();
};
