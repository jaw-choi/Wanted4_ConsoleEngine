#pragma once

namespace Wanted
{
    class Actor
    {
    public:
	Actor();
	virtual ~Actor();

	virtual void BeginPlay();
	virtual void Tick(float dt);
	virtual void Draw();

    protected:

    };
}