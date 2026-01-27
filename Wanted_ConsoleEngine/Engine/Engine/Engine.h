#pragma once
#include "Common/Common.h"

namespace Wanted
{
    //Main game engine class
    //객체
    class WANTED_API Engine
    {
        //데이터 전용.
        //Down/Up/Key
        struct KeyState
        {
            //현재 키가 눌렸는지
            bool isKeyDown = false;
            //이전에 키가 눌렸는지
            bool wasKeyDown = false;
        };

        public:
            //Constructor
            Engine();
            //Destructor
            ~Engine();


            //Run the main game loop
            void Run();
            void QuitEngine();
            
            //입력 확인 함수
            //이전에 입력이 안됐는데, 지금 눌렸으면 한 번 호출.
            bool GetKeyDown(int keyCode) const;
            //이전에 입력이 됐는데, 지금 안눌렸으면 한 번 호출.
            bool GetKeyUp(int keyCode) const;
            //키가 눌려있는지 계속 확인.
            bool GetKey(int keyCode) const;
            //새 레벨을 추가(설정)하는 함수.
            void SetNewLevel(class Level* newLevel);
    private:
        //입력 처리 함수
        void ProcessInput();

        //게임 플레이 시작 함수
        // Unity의 경우: Start/Awake
        void BeginPlay();

        //업데이트 함수
        void Tick(float deltaTime);

        //그리기 함수
        void Draw();
    private:
        //엔진 종료 플래그.
        bool isQuit = false;

        //키 상태 저장용 배열.
        KeyState keyStates[255] = { };

        Level* mainLevel = nullptr;

    };
}

