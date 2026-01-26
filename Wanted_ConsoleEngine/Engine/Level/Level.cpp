#include "Level.h"
#include "Actor/Actor.h"
namespace Wanted
{
    Level::Level()
    {
    }
    Level::~Level()
    {
        //메모리 정리
        for (Actor*& actor : actors)
        {
            //액터 객체 메모리 해제
            if (actor)
            {
                delete actor;
                actor = nullptr;
            }
        }

        actors.clear();
    }
    void Level::BeginPlay()
    {
        //액터에 이벤트 흘리기
        for (Actor*& actor : actors)
        {
            //TODO: 이미 BeginPlay 호출된 액터는 건너뛰기.
            actor->BeginPlay();
        }
    }
    void Level::Tick(float deltaTime)
    {
        for (Actor*& actor : actors)
        {
            //액터에 이벤트 흘리기
            actor->Tick(deltaTime);
        }
    }
    void Level::Draw()
    {
        for (Actor*& actor : actors)
        {
            //액터에 이벤트 흘리기
            actor->Draw();
        }
    }
}