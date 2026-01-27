#include <iostream>
#include "Engine/Engine.h"
#include "Level/TestLevel.h"
#include "Actor/Actor.h"
#include "Actor/TestActor.h"
#include "Level/Level.h"


int main()
{
    Wanted::Engine engine;
    engine.SetNewLevel(new TestLevel());
    engine.Run();
}