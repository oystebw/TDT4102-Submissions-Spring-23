#include "EmptyFace.h"

EmptyFace::EmptyFace(Point p, int r): Face{p, r}{}

void EmptyFace::draw(AnimationWindow& win){
    Face::draw(win);
    win.draw_circle({centre.x - radius / 3, centre.y - radius / 3}, radius / 5, Color::blue);
    win.draw_circle({centre.x + radius / 3, centre.y - radius / 3}, radius / 5, Color::blue);
}