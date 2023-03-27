#pragma once
#include "Face.h"

class EmptyFace: public Face{
    protected:

    public:
        EmptyFace(Point p, int r);
        void draw(AnimationWindow&) override;
        virtual ~EmptyFace(){};
};