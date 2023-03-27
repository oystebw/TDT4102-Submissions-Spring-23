#include "Face.h"

void Face::draw(AnimationWindow& win){
    win.draw_circle(centre, radius, Color::yellow);
}