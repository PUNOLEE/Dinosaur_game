//
// Created by PUNO_ on 12/4/18.
//

#pragma once

#include "model.h"
#include "view.h"
#include <ge211.h>

using namespace std;
using namespace ge211;

class Controller : public Abstract_game
{
public:
  explicit Controller(Position pos = {0, 24});

protected:
  Dimensions initial_window_dimensions() const override;
  string initial_window_title() const override;
  void on_key_down(Key) override;
  void on_key_up(Key) override;
  void on_frame(double) override;

  void draw(Sprite_set &) override;

  void on_start() override;

private:
  Model model_;
  View view_;

  // Game duration;
  double dur_;
};