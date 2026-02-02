#include "SokobanLevel.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"

#include <iostream>
/*
* #:벽
* .:바닥
* P:Player
* B:Box
* T:Target
*/


SokobanLevel::SokobanLevel()
{
	// Player 액터를 레벨에 추가.
	//AddNewActor(new Player());
    LoadMap("Stage1.txt");
}

void SokobanLevel::LoadMap(const char* filename)
{
    //파일 로드.
    //최종 파일 경로 만들기.
    char path[2048] = {};
    sprintf_s(path, 2048, "../Assets/%s", filename);

    //파일 열기
    FILE* file = nullptr;
    fopen_s(&file, path, "rt");

    //Exception
    if (!file)
    {
	// 표준 오류 콘솔 활용. 
	std::cerr << "Failed to open map file.\n";
	//디버그 모드에서 중단점으로 중단해주는 기능. 
	__debugbreak();
    }

    //맵 읽기.
    //맵 크기 파악 : File Position 포인터를 파일의 끝으로 이동.
    fseek(file, 0, SEEK_END);

    //이 위치 읽기
    size_t fileSize = ftell(file);

    // File Position 처음으로 되돌리기.
    rewind(file);

    //파일에서 데이터를 읽어올 버퍼 생성.
    char* data = new char[fileSize + 1]; //null문자 때문에 +1

    //데이터 읽기
    size_t readSize = fread(data, sizeof(char), fileSize, file);

    //객체를 생성할 위치 값.
    Wanted::vec2 position;


    // 읽어온 문자열을 분석(파싱-parsing)해서 출력.
    int index = 0;
    while (true)
    {
	if (index >= fileSize)
	{
	    break;
	}

	// 캐릭터 읽기.
	char mapCharacter = data[index];
	++index;

	// 개행 문자 처리.
	if (mapCharacter == '\n')
	{
	    std::cout << "\n";
	    ++position.y;
	    position.x = 0;
	    continue;
	}

	switch (mapCharacter)
	{
	case '1':
	    //std::cout << "#";
	    AddNewActor(new Wall(position));
	    break;
	case '.':
	    AddNewActor(new Ground(position));
	    //std::cout << " ";
	    break;
	case 'p':
	    //std::cout << "P";
	    AddNewActor(new Player(position));
	    AddNewActor(new Ground(position));
	    break;
	case 'b':
	    //std::cout << "B";
	    // 박스는 이동 가능함
	    // 박스가 옮겨졌을 때 그 밑에 땅이 있어야함
	    AddNewActor(new Box(position));
	    AddNewActor(new Ground(position));
	    break;
	case 't':
	    //std::cout << "T";
	    AddNewActor(new Target(position));
	    break;
	}

	//x좌표 증가 처리.
	++position.x;
    }

    // 사용한 버퍼 해제.
    delete[] data;


    //파일이 정상적으로 열렸으면 닫기.
    fclose(file);
}

bool SokobanLevel::CanMove(const Wanted::Vector2& playerPosition, const Wanted::Vector2& nextPosition)
{
    // 레벨에 있는 박스 액터 모으기.
    // 박스는 플레이어가 밀기 등 추가적으로 처리해야하기 때문.
    std::vector<Actor*> boxes;
    // 레벨에 배치된 전체 액터를 순회하면서 박스 찾기.
    for (Actor* const actor : actors)
    {
	// 액터가 박스 타입인지 확인.
	if (actor->IsTypeOf<Box>())
	{
	    boxes.emplace_back(actor);
	    continue;
	}
    }
    return false;
}
