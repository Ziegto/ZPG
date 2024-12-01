#pragma once

class AbstractObject
{
public:
    virtual ~AbstractObject() = default;
    virtual void draw() = 0;
};
