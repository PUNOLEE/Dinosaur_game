//
// Created by PUNO_ on 12/4/18.
//

#pragma once

#include <ge211.h>
#include "model.h"
#include <string>
using namespace ge211;

class View
{
public:
  explicit View(Model const &);

  /// Renders the current state of the model.
  void draw(Sprite_set &);

  /// The actual screen dimensions of the required game window.
  Dimensions screen_dimensions() const;

private:
  /// The model.
  Model const &model_;

  /// resources path
  string path_ = "../../../../resource/";

  /// font
  Font const sans_{path_ + "slkscr.ttf", 22};

  /// The sprites.
  // dino:
  Image_sprite const dino{path_ + "1x-trex-1.png"};
  // cloud:
  Image_sprite const cloud{path_ + "1x-cloud.png"};
  // flying obstacle:
  Image_sprite const fob{path_ + "flying.png"};
  // tree obstacle:
  Image_sprite const one_ob{path_ + "1x-one-ob.png"};
  Image_sprite const two_ob{path_ + "1x-two-ob.png"};
  Image_sprite const three_ob{path_ + "1x-three-ob.png"};
  // coin:
  Image_sprite const coin{path_ + "coin.png"};
  // text:
  Image_sprite const text_game_over{path_ + "1x-go.png"};
  // ground:
  Image_sprite const ground{path_ + "1x-horizon.png"};
  // start over:
  Image_sprite const startover{path_ + "1x-restart-1.png"};
  // running time
  Text_sprite rtsprite;
  // running distance
  Text_sprite rdsprite;
  // coin nums
  Text_sprite cnsprite;
};
