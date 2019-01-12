#pragma once

class IBombAction{
public:
    virtual ~IBombAction(){}
    virtual void Explode()=0;
};