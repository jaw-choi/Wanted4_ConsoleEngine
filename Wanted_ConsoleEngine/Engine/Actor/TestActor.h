#pragma once

#include "Actor.h"

class WANTED_API TestActor : public Wanted::Actor
{
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
};
