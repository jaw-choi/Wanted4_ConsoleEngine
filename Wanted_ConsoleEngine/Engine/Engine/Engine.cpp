#include "Engine.h"
#include <iostream>
#include <Windows.h>

namespace Wanted
{
    Engine::Engine()
    {
    }
    Engine::~Engine()
    {
    }

    void Engine::Run()
    {
            //시계의 정밀도
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);

        //프레임 계산용 변수
        //int64_t
        __int64 currentTime = 0;
        __int64 previousTime = 0;

        //하드웨어 타이머로 시간 구하기
        LARGE_INTEGER time;
        QueryPerformanceCounter(&time);
        //엔진 시작 직전에는 두시간 값을 같게 맞춤
        currentTime = time.QuadPart;
        previousTime = currentTime;

        //초당 프레임 수
        float targetFrameRate = 120.0f;
        float oneFrameTime = 1.0f / targetFrameRate;
        //Engine Loop(Game Loop)
        while (!isQuit)
        {
            //현재 시간 구하기
            QueryPerformanceCounter(&time);
            currentTime = time.QuadPart;


            //프레임 시간 계산
            float delta_time = static_cast<float>(currentTime - previousTime);

            //초단위 변환
            delta_time = delta_time / static_cast<float>(frequency.QuadPart);
            

            //프레임 처리
            //고정 프레임 기법
            if (delta_time >= oneFrameTime) {

                ProcessInput();
                Tick(delta_time);
                Draw();

                //이전 시간 값 갱신
                previousTime = currentTime;

                //현재 입력 값을 이전 입력 값으로 저장.
                for (int ix = 0; ix < 255; ++ix)
                {
                    keyStates[ix].wasKeyDown = keyStates[ix].isKeyDown;
                }
            }
        }
    //TODO: 정리작업
        std::cout << "Engine has been Shutdown..." << std::endl;
    }
    void Engine::QuitEngine()
    {
        isQuit = true;
    }

    bool Engine::GetKeyDown(int keyCode) const
    {
        return keyStates[keyCode].isKeyDown && !keyStates[keyCode].wasKeyDown;
    }

    bool Engine::GetKeyUp(int keyCode) const
    {
        return !keyStates[keyCode].isKeyDown && keyStates[keyCode].wasKeyDown;

    }

    bool Engine::GetKey(int keyCode) const
    {
        return keyStates[keyCode].isKeyDown;

    }

    void Engine::ProcessInput()
    {
        //키 마다의 입력 읽기.
        // !!! 운영체제가 제공하는 기능을 사용할 수 밖에 없음
        for (int ix = 0; ix < 255; ++ix)
        {
            keyStates[ix].isKeyDown
                = GetAsyncKeyState(ix) & 0x8000 > 0 ? true : false;
        }
    }

    void Engine::Tick(float deltaTime)
    {
        std::cout << "Delta Time: " << deltaTime
                  << ", FPS " << (1.0f / deltaTime) <<std::endl;
        // ESC키 누르면 종료
        if(GetKeyDown(VK_ESCAPE))
        {
            QuitEngine();
        }
    }

    void Engine::Draw()
    {
    }

}