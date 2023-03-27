#pragma once
#include "Emoji.h"

class Face: public Emoji{
    private:
    protected:
        Point centre;
        int radius;
    public:
        Face(Point c, int r): Emoji(), centre{c}, radius{r}{}
        virtual void draw(AnimationWindow&) override = 0;
        virtual ~Face(){};
};