#pragma once

#include "Actor.h"

class TestActor : public Wanted::Actor
{
public:
    virtual void BeginPlay() override;
    virtual void Tick(float deltaTime) override;
    virtual void Draw() override;
//runtime에는 접근제한자 상관없음 private이든 protected이든
};

