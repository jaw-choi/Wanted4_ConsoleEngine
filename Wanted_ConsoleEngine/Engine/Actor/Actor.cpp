#include "Actor.h"
#include "Util/Util.h"
#include "Render/Renderer.h"

#include <iostream>
#include <Windows.h>

namespace Wanted
{
	Actor::Actor(
		const char* image, 
		const Vector2& position,
		Color color)
		:position(position), color(color)
	{
	    // 문자열 복사. (RAII)
	    size_t length = strlen(image) + 1;  // 문자열의 길이를 구하고 널 종료 문자 크기를 추가
	    this->image = new char[length];      // 문자열을 저장할 메모리 동적 할당
	    strcpy_s(this->image, length, image); // 안전하게 문자열을 복사

	}

	Actor::~Actor()
	{
	    SafeDeleteArray(image);
	}

	void Actor::BeginPlay()
	{
		// 이벤트를 받은 후에는 플래그 설정.
		hasBeganPlay = true;
	}

	void Actor::Tick(float deltaTime)
	{
	}

	void Actor::Draw()
	{
		//Renderer::Draw(position, color, image);
		// 렌더러에 데이터 제출.
	    Renderer::Get().Submit(image, position, color, sortingOrder);
		
	}

	void Actor::SetPosition(const Vector2& newPosition)
	{
		// 렌더러에 빈칸 그리기 요청.
		//Renderer::Draw(position, ' ');

	    if (position == newPosition)
		return;

		// 새로운 위치 설정.
		position = newPosition;
	}
}