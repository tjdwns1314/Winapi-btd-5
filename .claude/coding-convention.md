# 코딩 컨벤션

이 저장소(Winapi-btd-5)에서 코드를 작성/수정할 때 따르는 규칙입니다.

## 타입 / 자료구조

- 원시 `int`/POINT 연산 대신, [Common/pch.h](../Common/pch.h)의 타입 별칭(`int32`, `uint32`, `int8` 등)과 [Common/Util.h](../Common/Util.h)의 `Vector`/`Cell`/`GridInfo` 구조체를 프로젝트 전역에서 우선 사용합니다.
- `Util.h`에 정의된 `RenderLayer`, `ActorType`, `SceneType`, `ColliderType`, `DirType` 같은 열거형이 게임의 분류 체계(렌더 레이어 순서, 콜라이더 형태, 씬 타입 등)에 대한 기준(source of truth)입니다. 새 값을 추가할 때도 이 열거형들을 확장하세요.

## 클래스 구조

- 매니저류(전역에 하나만 존재해야 하는) 클래스는 `Singleton<T>` ([Engine/Singleton.h](../Engine/Singleton.h)) CRTP 베이스를 사용합니다. 예: `Game`, `TimeManager`, `SceneManager`.
- 게임 오브젝트는 `Actor` → `MovableActor` 상속 체인을 따릅니다. 위치를 가지지만 움직이지 않는 것은 `Actor`, 방향/속도를 가지고 매 프레임 이동하는 것은 `MovableActor`를 상속하세요.
- `Engine/`은 게임과 무관한 재사용 가능 레이어입니다. `Engine/` 코드는 `Client/`의 타입(Bloon, Tower, GameScene 등)을 참조해서는 안 됩니다.

## 주석 스타일

- 함수 본문에서 로직의 **흐름(단계)**을 설명할 때만 각 단계 앞에 `1.`, `2.`, `3.`... 처럼 번호를 매긴 한 줄 주석을 붙입니다.
- 흐름 설명이 아닌 변수/값 하나에 대한 부연 설명은 기존처럼 코드 옆에 `//`로 짧게 붙입니다. 모든 주석을 번호 매기라는 규칙이 아닙니다.
- 예시: [Client/Object/WaveManager.cpp](../Client/Object/WaveManager.cpp)의 `StartNextWave()`, `spawnNext()`, `buildRound()`.

```cpp
void Example::DoSomething()
{
	int32 count = 0; // 변수 설명은 이렇게 옆에 짧게

	// 1. 첫 번째 단계 설명
	...

	// 2. 두 번째 단계 설명
	...

	// 3. 세 번째 단계 설명
	...
}
```

## 인코딩

- 소스 코드 주석은 한글로 작성합니다.
- 모든 `.h`/`.cpp` 파일은 UTF-8(BOM 포함)으로 저장합니다. `.editorconfig`와 `.vscode/settings.json`이 이를 강제하도록 설정되어 있습니다.
- BOM 없이 저장하면 MSVC가 시스템 코드페이지(CP949)로 오인해 한글 주석이 깨질 수 있으니, 새 파일을 만들거나 다른 도구로 파일을 저장할 때 인코딩을 확인하세요.
