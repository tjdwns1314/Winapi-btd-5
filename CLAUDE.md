# CLAUDE.md

이 파일은 Claude Code(claude.ai/code)가 이 저장소에서 작업할 때 참고하는 가이드입니다.

## 주의사항
- 너는 winapi 시니어 개발자야.
- 사용자와의 대화와 문서 설명은 한국어로 작성한다.
- 코드 식별자와 로그는 원문을 유지한다.
- 결과를 먼저 보고하고, 검증하지 않은 내용은 `미검증`으로 명시한다.
- 수정 파일과 중요한 위치는 파일 경로와 라인 링크로 보고한다.
- 질문하는 사람이 애매모호하게 질문을 하면 .claude/skills/clarify-ambiguous-request 를 실행시켜
- 사용자가 질문을 하였을 떄 여러가지 대안이 있다면 대안을 다 알려준 후에 가장 권장하는 방식을 맨 위 항목에 띄운 후에 `(recommend)` 를 붙여.
- c++20 문법을 기준으로 해야해
- 사용자가 커밋을 요청할 때마다 [.claude/commit-convention.md](.claude/commit-convention.md)를 먼저 읽고 그 규칙(Gitflow, 커밋 메시지 형식, Co-authored-by 금지 등)을 적용해 커밋한다.
- 코드를 수정하기 전에는 항상 사용자에게 먼저 허락을 받는다. 조사/탐색(파일 읽기, grep 등)은 자유롭게 하되, 실제 파일 수정(Edit/Write)은 어떤 파일을 어떻게 바꿀지 먼저 코드(diff/스니펫)로 보여준다.
- 사용자가 무언가를 해달라고 요청하면(코드 수정 등 실행 단계에서), 먼저 코드(diff/스니펫)를 보여준 뒤 "제가 직접 진행할까요?" 한 가지만 묻는다. 다른 형태의 질문(예/아니오 여러 개, 별도 옵션 추가 등)으로 대체하지 않는다. 사용자가 진행을 승인하면 그때 Edit/Write로 적용한다. 여러 파일을 고치는 작업이라도 한 번에 전체 계획을 코드로 보여주고 승인만 받으면 되고, 파일 하나하나마다 다시 물어볼 필요는 없다.
- 위 원칙은 예외 없이 아래 3단계 순서를 무조건 지킨다. 사용자가 "바로 해줘", "알아서 해줘"처럼 말하지 않는 한, 스스로 "바로 적용할게요"라고 말하고 이어서 Edit/Write를 호출하는 것도 금지다.
  1. diff(또는 코드 스니펫)를 먼저 보여준다.
  2. 진행할지 말지 사용자에게 물어본다.
  3. 사용자의 답변에 따라(승인이면 적용, 아니면 대기/수정) 그에 맞게 처리한다.
- 변경 설명은 프로즈(불릿 설명)가 아니라 실제 코드/diff로 보여준다. 이 원칙은 md 문서를 작성/수정할 때도 동일하게 적용한다.
- 빌드 검증(msbuild 등 컴파일 시도)은 Claude가 절대 직접 실행하지 않는다. 필요하면 사용자에게 명령어만 안내하고, 실행은 사용자가 직접 한다.
- 사용자가 오늘 작업 내용 정리를 요청하면(예: "오늘 한 거 정리해줘", "커밋메시지 만들어줘" 등), 다음 두 가지를 항상 함께 준비해서 보여준다.
  1. 깃허브 커밋 메시지 — [.claude/commit-convention.md](.claude/commit-convention.md) 규칙에 맞춰 요약해서 작성
  2. 오늘 작업한 내용 — 노션에 그대로 옮겨 붙일 수 있도록, 커밋 메시지보다 훨씬 자세하게 작성(무엇을/왜/어떻게 했는지 과정까지 포함)
     - 각 항목은 무엇을 했는지뿐 아니라 **왜/어떻게 했는지**까지 자세하게 정의해서 작성한다.
     - 전체 과정은 `1.` `2.` `3.` ... 번호 목록으로 순서대로 나열해서 작성한다.
     - 작업한 내용이 뭔지 주 제목을 쓰고 그 아래에 내용을 작성한다.
       내용은 이런식으로 번호를 써서 작성한다.
       1.2.3.4....


## 프로젝트

WinAPI + Direct2D로 직접 만든 풍선타워디펜스5 모작(Bloons TD 5 clone)입니다. 외부 게임 프레임워크 없이 엔진을 처음부터 직접 구현하는 학습용 프로젝트입니다.

## 작업·문서 절차

1. 관련 문서와 현재 변경 상태를 읽고 요청 범위를 확정한다.

## 빌드

Visual Studio C++ 솔루션이며, 별도의 CLI 빌드 스크립트는 없습니다. MSBuild 또는 Visual Studio를 직접 사용하세요.

```powershell
# 빌드 (저장소 루트에서, VS용 Developer PowerShell/명령 프롬프트 사용)
msbuild TowerDefense.sln /p:Configuration=Debug /p:Platform=x64
msbuild TowerDefense.sln /p:Configuration=Release /p:Platform=x64
```

- 툴셋: v143 (Visual Studio 2022), Windows SDK 10.0, C++ 미리 컴파일된 헤더 사용(`Common/pch.h`/`pch.cpp`).
- 구성(Configuration): Debug/Release, 플랫폼: Win32/x64.
- 이 저장소에는 자동화된 테스트나 린터가 설정되어 있지 않습니다.
- 진입점은 [Client/TowerDefense.cpp](Client/TowerDefense.cpp)의 `wWinMain`이며, 창을 생성하고 고정 프레임(120FPS 목표) 루프에서 `Game::Update()` / `Game::Render()`를 호출합니다.

## 아키텍처

코드는 계층 구조를 이루는 세 개의 폴더로 나뉩니다.

- **Engine/** — 게임과 무관하게 재사용 가능한 엔진 레이어(렌더링 래퍼, 액터 기반 클래스, 씬 기반 클래스, 타이밍, 싱글톤 헬퍼). `Client/`의 타입을 참조해서는 안 됩니다.
- **Client/** — Engine 위에 구축된 실제 타워디펜스 게임(게임 루프 오케스트레이션, 씬, 타워, 풍선, 발사체).
- **Common/** — 모든 곳에서 포함되는 공용 저수준 유틸리티/타입(`pch.h`, `framework.h`, `Util.h/cpp`, `Resource.h`). `pch.h`는 Direct2D(`d2d1.h`), WIC(`wincodec.h`), STL 컨테이너를 포함하고, 프로젝트 전역에서 쓰이는 타입 별칭(`int32`, `uint32` 등)과 `Vector` 수학 구조체를 정의합니다.

### 렌더링

렌더링은 고전적인 GDI 비트맵 블리팅이 아니라 **Direct2D + WIC**를 사용합니다(GDI가 PNG 알파 채널을 잘 다루지 못해서 의도적으로 선택한 방식). 핵심 구성 요소:

- `Graphic` ([Engine/Graphic.h](Engine/Graphic.h)) — `ID2D1Factory`, `ID2D1HwndRenderTarget`, `IWICImagingFactory`를 소유하며, `BeginDraw`/`EndDraw`/`Clear`와 비트맵 로딩을 래핑합니다.
- `Image` ([Engine/Image.h](Engine/Image.h)) — 로드된 PNG 하나(`ID2D1Bitmap`)와 그 크기를 담고 있으며, `DrawSprite`로 스프라이트 시트의 일부 영역을 그립니다.
- `SpriteAtlas` ([Engine/SpriteAtlas.h](Engine/SpriteAtlas.h)) — TexturePacker 스타일의 XML 아틀라스(`Res/InGame.xml`)를 이름별 `CellInfo` 사각형으로 로드하며, 이름으로 조회해 `Image::DrawSprite`에 전달합니다.
- 필요한 라이브러리는 [Client/Game.cpp](Client/Game.cpp)의 `#pragma comment`로 링크됩니다: `d2d1.lib`, `windowscodecs.lib`, `ole32.lib`.

### 게임 루프 / 싱글톤

`Game` ([Client/Game.h](Client/Game.h))은 `Singleton<T>` ([Engine/Singleton.h](Engine/Singleton.h))이며, `Graphic`과 현재 `GameScene`을 소유하고 `Init` → 매 프레임 `Update`/`Render` → `Cleanup` 흐름을 이끕니다. `TimeManager`(역시 싱글톤, [Engine/TimeManager.h](Engine/TimeManager.h))는 매 프레임 델타타임/FPS를 계산하고, 지연/반복 콜백을 위한 간단한 타이머 목록(`AddTimer`/`Remove`)을 관리합니다. `Singleton<T>` CRTP 베이스는 이 코드베이스에서 매니저류 클래스(Game, TimeManager, SceneManager 등)의 표준 패턴입니다.

### 액터와 게임플레이 객체

`Actor` ([Engine/Actor.h](Engine/Actor.h))는 기본 게임 오브젝트 타입으로, 위치/스케일/회전, `Update`/`Render`, 충돌 스타일 훅(`OnEnter`/`OnStay`/`OnExit`), 소유 `Scene`, 레이어, pending-kill 플래그를 가집니다. `MovableActor`는 여기에 방향/속도와 `Move` 스텝을 추가합니다. 게임플레이 타입들은 이를 기반으로 만들어집니다.

- `Bloon` ([Client/Bloon.h](Client/Bloon.h)) — `MovableActor`; 풍선 타입/HP는 [Client/BloonType.h](Client/BloonType.h)의 `BloonType`/`BloonColor`로 정의되며, 여기에는 앞으로 구현할 풍선 등급/터짐 체인(Red → Blue → ... → Ceramic)이 문서화되어 있습니다.
- `Tower`와 `Projectile` ([Client/Tower.h](Client/Tower.h), [Client/Projectile.h](Client/Projectile.h))은 현재 비어 있는 스텁 클래스이며 앞으로 구현해야 합니다.
- `GameScene` ([Client/GameScene.h](Client/GameScene.h))은 레벨 배경 `Image`와 `SpriteAtlas`를 소유하며, 씬별 액터 관리가 이루어질 곳입니다.

설계상 언급되지만 아직 자리만 잡혀 있거나 주석 처리된 부분들도 있습니다. 특히 `Scene` ([Engine/Scene.h](Engine/Scene.h), 전체가 주석 처리됨)과 `SceneManager` ([Engine/SceneManager.h](Engine/SceneManager.h), 빈 싱글톤 껍데기)이며, `GameScene`은 아직 `Scene`을 상속하지 않습니다. 씬 전환 로직을 구현할 때는 이 두 개도 함께 채워 넣어야 할 것입니다.

### 컨벤션

타입/자료구조, 클래스 구조, 인코딩 등 코딩 컨벤션은 [.claude/coding-convention.md](.claude/coding-convention.md)를 참고하세요.
커밋 메시지 형식과 Gitflow 브랜치 전략은 [.claude/commit-convention.md](.claude/commit-convention.md)를 참고하세요.
