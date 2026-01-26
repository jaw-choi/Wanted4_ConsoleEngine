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
            if (actor->HasBeganPlay())
            {
                continue;
            }

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
    void Level::AddNewActor(Actor* newActor)
    {
        //TODO: 나중에 프레임 처리 고려해서 따로 추가 작업 해야 함.
        actors.emplace_back(newActor);
        //push_back lvalue ref 받음-> 복사
        //emplace_back rvalue ref 받음 -> 임시값으로 보고 복사x, 참조전달함
    }
}