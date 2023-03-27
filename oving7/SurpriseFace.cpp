#include "SurpriseFace.h"

SurpriseFace::SurpriseFace(Point p, int r): EmptyFace{p, r}{}

void SurpriseFace::draw(AnimationWindow& win){
    EmptyFace::draw(win);
    win.draw_circle({centre.x, centre.y + radius / 2}, radius / 3, Color::red);

}