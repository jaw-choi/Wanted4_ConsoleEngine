#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Box.h"
#include "Level/Level.h"

#include "Interface/ICanPlayerMove.h"

#include <iostream>
#include <Windows.h>

using namespace Wanted;

Player::Player(const vec2& position)
//: Actor()
    : super('P', position, Color::Red) //text로 타입정보남겨서 텍스트로 읽어오기
{
    sortingOrder = 10;
}


void Player::BeginPlay()
{
    // 상위 함수 호출.
    // C++는 부모함수 가리키는 포인터가 없음.
    Actor::BeginPlay();

    //std::cout << "Player::BeginPlay().\n";
}

void Player::Tick(float deltaTime)
{
    super::Tick(deltaTime);

    // Q키 종료.
    if (Wanted::Input::Get().GetKeyDown('Q'))
    {
        // Todo: 게임 엔진 종료 요청.
        Wanted::Engine::Get().QuitEngine();
    }

    //if (Input::Get().GetKey('D'))
    if (Input::Get().GetKey(VK_SPACE))
    {
        if (owner)//poiner다룰때 항상 null check하기
        {
            owner->AddNewActor(new Box(GetPosition()));
        }
    }

    //인터페이스 확인
    static ICanPlayerMove* canPlayerMoveInterface = nullptr; // (주의)static 붙이면 최초 한번만 실행됨
    if (!canPlayerMoveInterface && GetOwner())
    {
        ICanPlayerMove* canPlayerMoveInterface = dynamic_cast<ICanPlayerMove*>(GetOwner());
    }

    // 이동.
    if (Input::Get().GetKeyDown(VK_RIGHT) && GetPosition().x < 20)
    {
        // 이동 가능 여부 판단.
        Vector2 newPosition(GetPosition().x + 1, GetPosition().y);
        if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
        {
            SetPosition(newPosition);
        }
        //Vector2 newPosition = GetPosition();
        //newPosition.x += 1;
        //SetPosition(newPosition);
    }

    if (Input::Get().GetKeyDown(VK_LEFT) && GetPosition().x > 0)
    {
        // 이동 가능 여부 판단.
        Vector2 newPosition(GetPosition().x - 1, GetPosition().y);
        if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
        {
            SetPosition(newPosition);
        }

        //Vector2 newPosition = GetPosition();
        //newPosition.x -= 1;
        //SetPosition(newPosition);
    }
    if (Input::Get().GetKeyDown(VK_UP) && GetPosition().y > 0)
    {
        // 이동 가능 여부 판단.
        Vector2 newPosition(GetPosition().x, GetPosition().y - 1);
        if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
        {
            SetPosition(newPosition);
        }

        //Vector2 newPosition = GetPosition();
        //newPosition.y -= 1;
        //SetPosition(newPosition);
    }

    if (Input::Get().GetKeyDown(VK_DOWN) && GetPosition().y < 15)
    {
        // 이동 가능 여부 판단.
        Vector2 newPosition(GetPosition().x, GetPosition().y + 1);
        if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
        {
            SetPosition(newPosition);
        }

        //Vector2 newPosition = GetPosition();
        //newPosition = newPosition - Vector2::Up;
        ////newPosition.y += 1;
        //SetPosition(newPosition);
    }

    //std::cout
    //	<< "Player::Tick(). deltaTime: " << deltaTime
    //	<< ", FPS: " << (1.0f / deltaTime) << "\n";
}

void Player::Draw()
{
    Actor::Draw();
}
