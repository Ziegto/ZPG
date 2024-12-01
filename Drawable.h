#pragma once
#include "ComposedTransform.h"
class Drawable
{
public:
    virtual void setTransformation(ComposedTransform* transform) = 0;
    virtual void draw(GLenum mode, int start, int count) = 0;
};
