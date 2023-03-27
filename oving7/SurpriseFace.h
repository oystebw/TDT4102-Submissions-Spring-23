#pragma once
#include "EmptyFace.h"

class SurpriseFace: public EmptyFace{
    protected:

    public:
        SurpriseFace(Point p, int r);
        void draw(AnimationWindow&) override;
        virtual ~SurpriseFace(){};
};