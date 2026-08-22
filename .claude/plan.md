# WinAPI 기반 절차적 풍선 타워 디펜스 기획서

## 1. 프로젝트 개요

| 항목 | 내용 |
|---|---|
| 프로젝트명 | Balloon Defense (가칭) |
| 장르 | 2D 타워 디펜스 |
| 개발 기간 | 4주 |
| 개발 환경 | C++20, WinAPI, Direct2D + WIC |
| 핵심 기술 | 타일맵 기반 렌더링, 타워/장애물 설치에 따른 A* 동적 경로 재탐색, 위험도 가중 A*(특수 풍선용) |
| (구현 현황) | 타일맵 전체를 Path로 채우고 테두리 임의 시작/도착점 사이를 A*로 계산해 풍선이 따라감. 타워·장애물 설치 시 셀 점유(`MapSystem::TryOccupyCell`) 여부로 경로를 재계산. 타워 4종·풍선 등급 체인·보스·특수 풍선·웨이브 30라운드·경제·세이브/로드까지 모두 구현 완료 |
| 목표 | 매번 달라지는 맵에서 풍선을 막는 싱글플레이 타워 디펜스 제작 |

플레이어는 골드를 사용해 타워와 장애물을 설치하고, 생성 지점에서 목표 지점으로 이동하는 풍선 형태의 적을 처치한다. 맵 전체는 기본적으로 풍선이 이동 가능한 타일이며, 플레이어가 타워·장애물을 놓으면 그 칸이 점유되어 막히고, A* 알고리즘이 시작점~도착점 경로를 다시 계산해 풍선의 이동 경로가 그때그때 바뀐다. `TileType`에는 `Path`/`Buildable`/`Obstacle` 열거값이 있지만, 실제로는 타일 종류를 미리 구분해 두는 대신 `MapSystem::TryOccupyCell`/`ReleaseCell`로 "경로가 아닌 칸이면 어디든 설치 가능"하게 동작한다(`TileType::Buildable`은 주석에만 등장하고 실사용되지 않음, [Client/Algorithm/PathFinder.h:17](../Client/Algorithm/PathFinder.h#L17)).

## 2. 핵심 게임 규칙

| 항목 | 내용 |
|---|---|
| 승리 조건 | 30라운드 전체 클리어 |
| 패배 조건 | 적이 도착 지점에 도달해 라이프가 0이 됨 |
| 초기 라이프 | 150 (`HealthManager::Init`, [Client/Scene/GameScene.cpp:43](../Client/Scene/GameScene.cpp#L43)) |
| 초기 골드 | 650 (`EconomyManager::Init`, [Client/Scene/GameScene.cpp:44](../Client/Scene/GameScene.cpp#L44)) |
| 자원 | 적 처치·라운드 클리어 시 골드 획득, 타워·장애물 설치/업그레이드/판매에 사용 |
| 적 | Red→Blue→Green→Yellow→Pink→Black/White→Lead→Zebra→Rainbow→Ceramic 색상 등급 체인 + 특수 풍선(Special, 위험도 경로 전용) + 보스 풍선 2종(Boss1/Boss2, 내부에 하위 풍선을 담고 있음) |
| 타워 | 사거리 안의 적을 자동으로 탐지하여 공격, 4종 모두 구현 완료 |
| 장애물 | 타워와 별개로 배치 가능한 소모품형 오브젝트(`Obstacle`, 바나나팜 굴뚝류). 라운드 진행도에 따라 설치 한도가 늘어남 |
| 맵 | 격자 기반 타일 맵(18×13), 타워·장애물 설치 시 A*로 경로 재계산, 스테이지는 1개(1-1)만 구현 |
| 웨이브 | 30라운드 고정, 라운드마다 가중치 예산으로 등장 풍선 조합을 추첨해 순차 스폰 |

## 3. 타일맵과 시작/도착점

맵은 그리드 전체를 우선 `TileType::Path`(이동 가능)로 채운 뒤, 시작점·도착점을 테두리 셀 중에서 무작위로 뽑는다(`TileMap::GenerateRandomStartEndPoint`, [Client/Map/TileMap.cpp](../Client/Map/TileMap.cpp)). 이후 [4절](#4-a-알고리즘-활용)의 A*가 이 두 점 사이 경로를 매 게임마다 다시 계산한다. 세이브 데이터를 불러올 때는 `MapSystem::Init`에 저장된 `startCell`/`endCell`을 그대로 넘겨 랜덤 재생성을 건너뛴다([Client/Map/MapSystem.h:13-14](../Client/Map/MapSystem.h#L13)).

### 타일 종류

| 리소스 | 의미 | 구현 상태 |
|---|---|---|
| `Resource/Tile1.png` | 풍선이 이동 가능한 길 (`TileType::Path`) | ✅ 렌더링 완료 |
| `Resource/Tile2.png` | 그 외 칸(설치 가능 칸) | ✅ 렌더링은 되지만 `TileType::Buildable` 열거값 자체는 배치 판정에 쓰이지 않음. 실제 설치 가능 여부는 `MapSystem::TryOccupyCell`이 "경로 위가 아니고 이미 점유되지 않은 칸"인지로 판정 |

### 시작/도착점 규칙

- 축(좌우/상하)을 무작위로 고른 뒤, 시작점은 한쪽 벽에서, 도착점은 **반대쪽 벽**에서 각각 독립적으로 무작위 좌표를 뽑는다.
- 시작점이 모서리에 찍히더라도 도착점 생성 로직에는 영향이 없다 — 두 값은 서로 완전히 독립적인 난수다.
- 그리드 한 칸 크기(`BLOCK_SIZE = 80`px, [Common/GameConfig.h:9](../Common/GameConfig.h#L9))는 타일 이미지 1장이 그려지는 크기와 같다.
- 웨이브 진행 중에는 풍선이 지나가는 경로 위에 타워/장애물을 설치할 수 없다(`ObstacleController::UpdateDrag`의 `waveActive && map.IsCellOnPath(...)` 체크, [Client/Object/ObstacleController.cpp:62-64](../Client/Object/ObstacleController.cpp#L62)).

## 4. A* 알고리즘 활용

`PathFinder::FindPath`([Client/Algorithm/PathFinder.cpp](../Client/Algorithm/PathFinder.cpp))가 [3절](#3-타일맵과-시작도착점)에서 정한 시작점~도착점 사이를 A*로 계산한다. 4방향 이동, 휴리스틱은 맨해튼 거리, Open 리스트는 `std::priority_queue` 기반 최소 힙이다. 타워/장애물이 설치·판매될 때마다 `MapSystem::recomputePath()`가 이 경로를 다시 계산한다.

문서에는 없던 확장으로 `PathFinder::FindRiskPath`가 추가되었다: 설치된 타워의 사거리(`RiskSource`)가 겹치는 칸일수록 이동 비용이 커지도록 가중치를 주는 A*로, 10라운드부터 등장하는 **특수 풍선(Special) 전용 경로**를 계산한다(`kRiskWeightPerTower = 1.0f`). 이 경로는 매 프레임이 아니라 특수 웨이브가 시작되는 시점에 한 번만 계산되며, 그 웨이브가 끝날 때까지는 타워가 추가로 배치되어도 갱신되지 않는다(`WaveManager::StartNextWave`가 `hasSpecialBloon`일 때만 `_onSpecialWaveStart()` 콜백 호출, [Client/Object/WaveManager.cpp:87-89](../Client/Object/WaveManager.cpp#L87)).

풍선(`Bloon`)은 이 경로(`vector<Vector>`)를 `BloonFactory::Create`로 전달받아 웨이포인트를 순서대로 따라 이동한다. 일반 풍선은 `_path`, 특수 풍선은 `_riskPath`를 따른다(`WaveManager::spawnNext`, [Client/Object/WaveManager.cpp:183](../Client/Object/WaveManager.cpp#L183)).

### 디버그 표시

| 대상 | 색상 | 함수 |
|---|---|---|
| 시작점 / 도착점 | 초록 / 빨강 | `MapSystem::RenderTiles` 계열 |
| 일반 경로 웨이포인트 | 파랑 | `MapSystem::RenderPathDebug` |
| 위험도 경로 웨이포인트 | 빨강 | `MapSystem::RenderRiskPathDebug` |

## 5. 풍선 등급 체계와 충돌 판정

### 풍선 등급 체인 (`Resource/Data/BloonType.json` 기준)

Red → Blue → Green → Yellow → Pink → Black/White → Lead → Zebra → Rainbow → Ceramic 체인에 더해, **보스 2종(Boss1, Boss2)과 특수 풍선(Special)**이 추가로 구현되어 있다.

**터짐 규칙(데미지 관통)**: `BloonPopResolver::resolve()`([Client/Object/BloonPopResolver.cpp:78-116](../Client/Object/BloonPopResolver.cpp#L78))가 재귀적으로 처리한다. 각 등급은 자신만의 "레이어 체력"을 갖고, 한 발의 공격 데미지가 현재 등급의 레이어 체력을 넘으면 초과분(leftover)이 하위 등급으로 이어져 즉시 재판정된다. 최하위 등급(Red)까지 도달하면 하위 개체 없이 그대로 삭제된다.

등급별 구성 (실제 데이터, [Resource/Data/BloonType.json](../Resource/Data/BloonType.json) 기준):

| 등급 | 레이어 체력 | 이동 속도 | 골드 보상 | 하위 개체 |
|---|---|---|---|---|
| Red | 1 | 150 | 1 | 없음(최하위) |
| Blue | 1 | 200 | 1 | Red ×1 |
| Green | 1 | 250 | 1 | Blue ×1 |
| Yellow | 1 | 300 | 1 | Green ×1 |
| Pink | 1 | 350 | 1 | Yellow ×1 |
| Black | 1 | 150 | 1 | Pink ×2 |
| White | 1 | 150 | 1 | Pink ×2 |
| Lead | **3** | 150 | 1 | Black ×2 |
| Zebra | 1 | 150 | 1 | Black ×1 + White ×1 |
| Rainbow | 1 | 150 | 1 | Zebra ×2 |
| Ceramic | 10 | 150 | 1 | Rainbow ×2 |
| Special | 2 | 150 | 2 | 없음. 위험도 가중 A* 경로(`FindRiskPath`)를 탐 |
| Boss1 | 200 | 100(고정) | 300 | Ceramic ×4 |
| Boss2 | 700 | 80(고정) | 500 | Boss1 ×4 |

> ⚠️ 이전 버전 문서의 "등급별 골드 보상 1~15 차등 지급" 표는 현재 데이터와 다르다. 일반 등급(Red~Ceramic)은 전부 골드 보상 1로 통일되어 있고, Special=2, Boss1=300, Boss2=500만 차등이다. Lead의 레이어 체력도 처음 기획한 1이 아니라 3으로 상향되었다(`06ebe24 fix: 납 풍선 레이어 체력 상향`).

**이동 속도**: 등급별 고정값을 `BloonType.json`의 `speed` 필드에서 직접 읽어온다. 기획 초안의 `Speed(tier) = 60 + 5 × (tier-1)` 공식은 사용되지 않으며, Red(150)~Pink(350)까지는 등급이 오를수록 빨라지다가 Black 이후로는 다시 150으로 고정된다. 보스는 등급 공식과 무관하게 Boss1=100, Boss2=80의 고정값을 쓴다.

**특수 풍선 등장**: 10라운드부터, 라운드당 30% 확률로 해당 라운드 스폰 순서 중 무작위 위치에 Special 20마리가 섞여 들어간다(`kSpecialWaveUnlockRound=10`, `kSpecialWaveChance=0.3f`, `kSpecialBloonCount=20`, [Client/Object/WaveManager.cpp:271-287](../Client/Object/WaveManager.cpp#L271)).

### 충돌 판정

| 대상 | 판정 방식 | 실제 구현 |
|---|---|---|
| 일반 풍선 (Red~Ceramic, Special) | 원형(Circle) | `ColliderCircle(this, BLOCK_SIZE/2 * kBloonBaseScale)`, [Client/Object/Bloon.cpp:43](../Client/Object/Bloon.cpp#L43) |
| 보스 풍선 (Boss1/Boss2) | 타원형(Ellipse) | `ColliderEllipse`, [Client/Object/Bloon.cpp:39](../Client/Object/Bloon.cpp#L39) |
| 투사체 | 원형(Circle) | `ColliderCircle(this, 20.f * kProjectileBaseScale)`, [Client/Object/Projectile.cpp:32](../Client/Object/Projectile.cpp#L32) |

> ⚠️ 이전 문서의 "일반 풍선=AABB, 보스=OBB" 설계는 실제로는 채택되지 않았다. 회전이 필요 없는 원형 콜라이더로 통일하되, 몸집이 긴 보스만 타원형 콜라이더를 쓴다. 또한 일반 풍선은 이동해도 회전하지 않고, 보스 풍선만 이동 방향에 맞춰 회전한다(`5b4a89c fix: 일반 풍선은 회전 하지 않음 보스 풍선만 회전함`).

### 보스 풍선

- 형태: 캡슐형 몸체, 이동 방향에 따라 회전(`spriteScale = 0.4`로 축소 렌더링).
- 자체 체력(레이어 체력)을 가지며, 그 체력이 0이 되면 파괴되어 하위 개체를 방출한다(컨테이너 역할). 처리 로직은 일반 풍선과 동일한 `BloonPopResolver` 경로를 탄다.
- 전용 피격/파괴 효과음 사용(`moab_damage_quieter`, `moab_destroyed_short`, [Client/Object/BloonPopResolver.cpp:33,57](../Client/Object/BloonPopResolver.cpp#L33)).
- 웨이브 가중치 테이블(8절)에는 보스가 별도 편입되어 있지 않다 — 현재는 상시 웨이브 로테이션이 아니라 별도 트리거 없이 구현만 되어 있는 상태(미검증: 실제 게임 플로우 중 보스가 언제 등장하는지는 코드상 별도 확인 필요).

## 6. UI 기획

- 창 해상도: **1760 × 1040** (`GWinSizeX/GWinSizeY`, [Common/GameConfig.h:5-6](../Common/GameConfig.h#L5))
- 게임(그리드) 화면: **1440 × 1040** (`GameAreaWidth/GameAreaHeight`)
- 그리드 칸수: **18 × 13**, `BLOCK_SIZE = 80`px (`GRID_COUNT_X = 1440/80 = 18`, `GRID_COUNT_Y = 1040/80 = 13`)
- 나머지 320px(1760-1440)는 우측 타워/UI 패널 영역

> ⚠️ 이전 문서의 "1440×1080 창, 24×16 그리드, BLOCK_SIZE=60" 수치는 레거시 값이다. 실제 코드 기준으로 창 크기와 그리드 칸수가 모두 변경되었다.

```text
┌───────────────────────────────────────────────────────┐
│ [웨이브] 3 / 30      [라이프] ♥ 150     [골드] $ 650   │
├───────────────────────────────┬───────────────────────┤
│                               │ 타워 선택 패널         │
│          절차 생성 맵          │ [다트원숭이] $200      │
│      시작점 → 길 → 도착점      │ [압정슈터]  $360      │
│                               │ [저격원숭이] $400      │
│                               │ [폭탄타워]  $650      │
│                               │ [장애물]                │
│                               │                       │
│                               │ 선택 타워 정보         │
│                               │ 판매 / 업그레이드      │
├───────────────────────────────┴───────────────────────┤
│ [시작 / 일시정지]        [배속] x1 / x2   [자동진행]   │
└───────────────────────────────────────────────────────┘
```

- 상단: 현재 라운드(1~30), 남은 라이프, 골드
- 중앙: 절차 생성 맵, 길, 타워, 장애물, 적, 투사체
- 오른쪽: 타워/장애물 구매 버튼과 선택된 대상의 정보
- 하단: 웨이브 시작, 배속 전환, 자동진행 토글
- 스페이스바로 웨이브 시작/배속 전환을 동시에 처리(`GameScene::onStartButtonClick`, [Client/Scene/GameScene.cpp:419-430](../Client/Scene/GameScene.cpp#L419)). 배속은 x1/x2(`kFastTimeScale = 2.0f`).
- 로비(`LobbyScene`)에는 스테이지 선택 팝업이 있고 ESC로 닫을 수 있다(`LobbySceneUI::openSelectPopup/closeSelectPopup`).

## 7. 타워 스탯 설계

### 공통 프로퍼티 (실제 구현: `TowerGradeStat`, [Client/Object/TowerType.h:12-27](../Client/Object/TowerType.h#L12))

문서 초안의 `_attackRange` 등 멤버명과 달리, 실제로는 타워가 등급별 스탯 구조체(`TowerGradeStat`)를 갖고 `Tower::GetStat()`으로 현재 등급의 스탯을 참조하는 구조다.

| 프로퍼티 | 타입 | 의미 |
|---|---|---|
| `damage` | float | 공격 데미지 |
| `attackRange` | float | 공격 사거리 |
| `attackSpeed` | float | 공격 주기(초) |
| `projectileSpeed` | float | 투사체 속도 |
| `attackCount` | int32 | 한 번의 공격으로 발사하는 투사체 개수 |
| `pierceCount` | int32 | 투사체 하나가 관통 가능한 풍선 수(다트원숭이 전용) |
| `splashRadius` | float | 스플래시 반경(폭탄타워 전용) |
| `cost` | int32 | 해당 등급으로 올라가는 업그레이드 비용 |

- **사거리 판정은 원형이 아니라 그리드 기준 정사각형**이다(`dff0035 refactor: 타워 공격 사거리를 원형에서 그리드 기준 정사각형으로 변경`). `PathFinder::FindRiskPath`도 동일 기준(`max(|dx|,|dy|) <= range`)을 사용한다. → 6절 사거리 공식(`attackRange = 40 + 80×n`, 원형 기준)은 더 이상 유효하지 않다.
- 업그레이드 시스템은 그대로 구현되어 있다: `_grade`(1부터 시작), `_canUpgrade`, `ApplyUpgrade()`, `GetNextUpgradeCost()`. 모든 타워는 등급 1(기본) + 업그레이드 4개 = 최대 등급 5로 통일.
- 데이터는 `Resource/Data/TowerType.json`에서 로드한다. 실수치는 밸런싱 완료된 값으로, placeholder(전부 1)가 아니다.

### 타워별 실제 수치 (`Resource/Data/TowerType.json` 기준)

#### 다트원숭이 (basePrice 200)

| 등급 | 업그레이드 | damage | attackRange | attackSpeed | attackCount | pierceCount | cost |
|---|---|---|---|---|---|---|---|
| 1 | - | 1 | 120 | 0.5 | 1 | 1 | - |
| 2 | 장거리 다트 | 1 | 200 | 0.5 | 1 | 1 | 100 |
| 3 | 날카로운 사격 | 1 | 200 | 0.5 | 1 | 2 | 120 |
| 4 | 아주 날카로운 사격 | 1 | 200 | 0.5 | 1 | 4 | 200 |
| 5 | 트리플 다트 | 1 | 200 | 0.5 | 3 | 4 | 300 |

#### 압정슈터 (basePrice 360, 회전 없음 — `rotatesToTarget: false`)

| 등급 | 업그레이드 | damage | attackRange | attackSpeed | attackCount | cost |
|---|---|---|---|---|---|---|
| 1 | - | 1 | 120 | 2.0 | 8 | - |
| 2 | 더 빠른 발사 | 1 | 120 | 1.8 | 8 | 200 |
| 3 | 광역 압정 | 1 | 200 | 1.8 | 8 | 250 |
| 4 | 훨씬 더 빠른 발사 | 1 | 200 | 1.4 | 8 | 450 |
| 5 | 압정 살포기 | 1 | 200 | 1.4 | 16 | 600 |

#### 저격원숭이 (basePrice 400, 무제한급 사거리)

| 등급 | 업그레이드 | damage | attackRange | attackSpeed | cost |
|---|---|---|---|---|---|
| 1 | - | 1 | 2000 | 2.0 | - |
| 2 | 풀 메탈 재킷 | 2 | 2400 | 2.0 | 150 |
| 3 | 빠른 저격 | 3 | 2400 | 1.6 | 300 |
| 4 | 야간 투시경 | 5 | 2400 | 1.6 | 400 |
| 5 | 치명적인 정밀함 | 10 | 2400 | 1.6 | 500 |

#### 폭탄타워 (basePrice 650)

| 등급 | 업그레이드 | damage | attackRange | attackSpeed | splashRadius | cost |
|---|---|---|---|---|---|---|
| 1 | - | 1 | 120 | 2.0 | 120 | - |
| 2 | 추가 사거리 | 1 | 200 | 2.0 | 120 | 150 |
| 3 | 거대 폭탄 | 1 | 200 | 2.0 | 160 | 250 |
| 4 | 풍선 충격 | 2 | 200 | 2.0 | 160 | 400 |
| 5 | 미사일 발사대 | 3 | 280 | 1.0 | 200 | 600 |

> ⚠️ 기획 초안의 구매 비용(다트원숭이 200/압정슈터 280/저격원숭이 350/폭탄타워 400)과 업그레이드 효과 설명은 방향성은 맞았으나 실제 수치·비용은 밸런싱을 거치며 달라졌다(압정슈터 360, 폭탄타워 650 등). 저격원숭이의 "강화탄/철갑탄/고폭탄" 업그레이드명은 실제로 "풀 메탈 재킷/야간 투시경/치명적인 정밀함"으로 바뀌었다.

### 타워별 차별화

| 타워 | 공격 판정 | 회전 여부 | 설명 |
|---|---|---|---|
| 다트원숭이 | 단일 타겟, 관통 가능 | 회전함 | 사거리 안 가장 가까운 적에게 다트 발사. 등급이 오르면 관통력·발사 개수 증가 |
| 압정슈터 | 전방위 다중 타겟(8~16개 동시 발사) | 회전 없음 | 짧은 사거리 대신 사방으로 압정을 뿌림 |
| 저격원숭이 | 단일 타겟, 초장거리 | 회전함 | 사거리가 사실상 맵 전체를 커버(2000~2400px). 공속은 느리지만 데미지가 높음 |
| 폭탄타워 | 스플래시 | 회전함 | 명중 지점 주변 범위 내 다수 적에게 동시 데미지 |

## 8. 웨이브 설계

- 스테이지 전체 **30라운드 고정**(`kRoundCount = 30`, [Client/Object/WaveManager.cpp:12](../Client/Object/WaveManager.cpp#L12)).
- **실제 구현은 "가중치 예산 기반 추첨" 방식**이며, 기획 초안의 `TotalCount(R) = base + growth×(R-1)` 공식형 서브웨이브 분배와는 알고리즘이 다르다.
  1. 라운드마다 "가중치 예산"을 계산한다: `weightBudget = 20 + 20 × (R-1)` (`kBaseWeightBudget=20`, `kGrowthWeightBudget=20`, [Client/Object/WaveManager.cpp:214](../Client/Object/WaveManager.cpp#L214)).
  2. 이 라운드에 등장 가능한(unlockRound~retireRound 범위 안) 등급들 중에서, 남은 예산 이하의 weight를 가진 등급들을 대상으로 `std::discrete_distribution`으로 가중치 비례 무작위 추첨을 반복한다. 뽑힐 때마다 예산에서 그 등급의 weight만큼 차감하고, 더 뽑을 수 있는 등급이 없으면 종료한다.
  3. 뽑힌 등급들이 그대로 그 라운드의 스폰 순서(`spawnOrder`)가 되며, 서브웨이브 개념 없이 등급이 섞인 하나의 스폰 큐로 순차 소환된다.
- 스폰 간격: `spawnInterval = max(0.3, 1.0 - 0.05×(R-1))` (초) — 문서 초안과 동일한 공식이 그대로 쓰인다.
- 서브웨이브 사이 대기시간 개념은 없다 — 라운드 전체가 하나의 스폰 큐이므로 등급이 바뀌어도 대기 없이 `spawnInterval` 간격으로 계속 스폰된다.

### 등급별 가중치와 등장/은퇴 라운드 (실제 테이블, `GetBloonWaveTable`)

| 등급 | weight | 등장 라운드 | 은퇴 라운드 |
|---|---|---|---|
| Red | 1 | 1 | 8 |
| Blue | 2 | 3 | 10 |
| Green | 3 | 5 | 12 |
| Yellow | 4 | 7 | 14 |
| Pink | 5 | 8 | - |
| Black | 6 | 10 | - |
| White | 6 | 10 | - |
| Lead | 10 | 13 | - |
| Zebra | 12 | 15 | - |
| Rainbow | 15 | 17 | - |
| Ceramic | 20 | 20 | - |

> ⚠️ 기획 초안의 weight/unlockRound/retireRound 수치와 다르다. 특히 Lead~Ceramic의 weight는 초안(7~10)보다 훨씬 커졌다(10~20).

### 라운드 클리어 보너스

`보너스 골드 = 99 + 클리어한 라운드 번호` (`kRoundClearBonusOffset = 99`, [Client/Object/WaveManager.cpp:44](../Client/Object/WaveManager.cpp#L44)). 초안의 `20 + 15×W` 공식은 사용되지 않는다.

### 특수 풍선 / 자동진행

- 10라운드부터 라운드당 30% 확률로 Special 20마리가 스폰 순서에 무작위로 섞인다([5절](#5-풍선-등급-체계와-충돌-판정) 참고).
- 자동진행(`SetAutoPlay`) 기능이 구현되어 있다 — 켜두면 라운드 클리어 후 `kAutoStartDelay = 1.0초` 뒤 자동으로 다음 라운드를 시작한다.

### 보스 등장

- `BloonColor::Boss1`/`Boss2`가 구현되어 있으나, 위 웨이브 가중치 테이블에는 포함되어 있지 않다. 정규 웨이브 로테이션을 통한 보스 등장 트리거는 **미검증** — 별도 확인 필요.

## 9. 투사체 설계

- `Client/Object/Projectile.h/.cpp`. 속도(`_speed`)는 타워 등급 데이터의 `projectileSpeed`를 그대로 사용(placeholder 아님, 예: 다트 1200, 압정 1000).
- 이동 방식: 유도 없이 발사 시점의 방향으로 직진, 발사 방향에 맞춰 스프라이트를 회전시킨다(`atan2f` 기반, [Client/Object/Projectile.cpp:34](../Client/Object/Projectile.cpp#L34)).
- 최대 사거리(`_maxDistance`)를 넘어가면 자동 소멸.
- 관통(`_pierceCount`/`_pierceRemaining`)과 스플래시(`_splashRadius`) 모두 구현됨: 스플래시가 있으면 폭발 이펙트(`EffectFactory::Create`)와 효과음(`explosion_small`)을 함께 재생하고 범위 내 모든 풍선에 동시 데미지를 준다.
- 콜라이더는 원형(`ColliderCircle`).

## 10. 씬 구성

- `Engine/Core/Scene.h`를 상속받는 `MainScene`, `LobbyScene`, `GameScene`, `EditorScene` 4개 씬으로 구성한다. `SceneManager`([Engine/Manager/SceneManager.h](../Engine/Manager/SceneManager.h))가 씬 전환을 관리한다.
- 진입 흐름: `MainScene`(타이틀) → `LobbyScene`(스테이지 선택 팝업, ESC로 닫기 가능) → `GameScene`(플레이).
- `EditorScene`은 게임플레이 씬이 아니라 스프라이트 아틀라스/UI 리소스를 미리 로드해 확인하는 내부 개발용 씬이다(HUD, 팝업, 업그레이드 아이콘 등 여러 리소스를 한 번에 로드).
- 스테이지는 1개(1-1)만 구현되어 있다. 문서 초안의 순차 잠금 해제(1-1→1-2→1-3) 설계는 스테이지가 하나뿐이라 아직 적용 대상이 없다.

## 11. 경제 설계 (골드 보상 / 타워 가격)

### 타워 구매 비용 (`Resource/Data/TowerType.json`)

| 타워 | 구매 비용 |
|---|---|
| 다트원숭이 | 200 |
| 압정슈터 | 360 |
| 저격원숭이 | 400 |
| 폭탄타워 | 650 |

### 타워 판매 / 업그레이드

- `TowerController::SellSelected`, `UpgradeSelected`가 `EconomyManager`와 연동되어 구현되어 있다. 정확한 환급 공식(구매가+업그레이드 누적×70%)은 초안대로인지 **미검증** — 코드 상세 확인 필요.
- 업그레이드 비용은 등급별로 `TowerType.json`의 `cost` 필드에 직접 명시되어 있다(고정 배율 공식이 아니라 타워마다 개별 지정). 예: 다트원숭이 100/120/200/300, 폭탄타워 150/250/400/600.

### 풍선 처치 골드 보상 (실제 데이터)

| 등급 | Red~Ceramic (전체 동일) | Special | Boss1 | Boss2 |
|---|---|---|---|---|
| 보상 | 1 | 2 | 300 | 500 |

> ⚠️ 초안의 등급별 차등 보상(1~15) 표는 현재 데이터와 다르다 — 실제로는 일반 등급이 전부 1로 통일되어 있다.

### 라운드 클리어 보너스

`99 + 클리어한 라운드 번호` ([8절](#8-웨이브-설계) 참고).

### 장애물 경제

- 장애물(`Obstacle`, 바나나팜 굴뚝류) 구매 비용은 `GetObstacleStat(ObstacleType::BananaFarmChimney).basePrice`로 관리되며, 설치 개수 상한이 라운드 진행에 따라 늘어난다: 기본 10개 → 10라운드부터 15개 → 20라운드부터 20개(`kObstacleBaseCount=10`, `kObstacleBonusCount=5`, [Client/Object/ObstacleController.cpp:13-27](../Client/Object/ObstacleController.cpp#L13)).
- 판매 시 `Obstacle::GetSellPrice()`만큼 환급.

## 12. 세이브/로드 (신규, 문서 초안에 없던 기능)

`Client/Core/SaveManager.h/.cpp`, `Client/Core/SaveData.h`로 구현되어 있다.

- 저장 대상: 골드, 라이프, 다음 라운드 번호, 자동진행/배속 여부, 맵의 시작·도착 셀, 배치된 타워 목록(타입+등급+셀), 배치된 장애물 목록(타입+셀).
- 웨이브가 `Idle` 상태일 때만 저장/로드 가능(라운드 진행 중 저장 불가).
- 로드 시 `TowerFactory::Create(type, worldPos)` 후 저장된 등급만큼 `ApplyUpgrade()`를 반복 호출해 타워 상태를 복원한다.
- 맵은 저장된 `startCell`/`endCell`을 그대로 사용해 랜덤 재생성을 건너뛴다(`MapSystem::Init(forcedStart, forcedEnd)`).

## 13. 오브젝트 풀 (`Engine/Core/ObjectPool.h`)

타워/투사체/풍선/이펙트/장애물 등 대부분의 `Actor` 파생 클래스가 오브젝트 풀로 관리된다(`PoolManager`, [Client/Object/PoolManager.h/.cpp](../Client/Object/PoolManager.h)).

- `PoolManager::Init(bloonSize, towerSize, obstacleSize, effectSize, projectileSize)`로 타입별 고정 크기 버퍼를 게임 시작 시 미리 할당한다(`GameScene::Init`에서 `Init(250, 200, 50, 50, 250)` 호출, [Client/Scene/GameScene.cpp:38](../Client/Scene/GameScene.cpp#L38) — 주석상 임시값).
- `Acquire()`/`Return()`으로 재사용. 최근 수정(미커밋, `git status` 기준)으로 `Acquire()`가 `std::destroy_at` + `std::construct_at`를 통해 재사용 직전 객체를 완전히 재생성하도록 바뀌는 중이다 — 커밋 `91721aa fix: 오브젝트 풀 재사용에 따른 풍선 렌더링 누락(투명화) 현상 해결`과 연관된 후속 작업으로 보이나, [Engine/Core/ObjectPool.h](../Engine/Core/ObjectPool.h)의 이 변경분은 아직 커밋되지 않았다(**미검증**: 최종적으로 어떤 형태로 커밋될지는 확정 전).

## 14. 구현 범위

### 완료된 기능

- WinAPI 창 생성 및 게임 루프
- 타일 기반 맵 렌더링, 매 게임 랜덤 시작/도착점 + A* 경로 계산
- 풍선 등급 체인(Red~Ceramic) + 특수 풍선(Special) + 보스 풍선(Boss1/Boss2) 구현 및 터짐 체인 처리
- 적 생성, 이동, 피격, 처치
- 타워 4종(다트원숭이/압정슈터/저격원숭이/폭탄타워) 설치, 사거리 판정(정사각형), 자동 타게팅, 투사체 공격(관통/스플래시)
- 타워 업그레이드(등급 5까지) 및 판매
- 장애물 설치/판매(라운드별 설치 한도 증가)
- 골드, 라이프, 라운드 UI, 배속(x1/x2), 자동진행
- 웨이브 30라운드(가중치 추첨 방식), 라운드 클리어 보너스
- 게임 오버 및 클리어 화면(팝업 리소스 존재, `game_over_popup`)
- 세이브/로드
- 씬 4개(MainScene/LobbyScene/GameScene/EditorScene), 로비 스테이지 선택 팝업(ESC 닫기)
- 오브젝트 풀 기반 Actor 재사용

### 미확인/추후 확인 필요 (미검증)

- 보스 풍선이 정규 웨이브 로테이션에서 실제로 언제·어떻게 등장하는지
- 타워 판매 환급 공식이 기획대로 (구매가+업그레이드 누적)×70%인지
- `ObjectPool` 미커밋 변경분의 최종 형태

### 아직 없는 기능

- 스테이지 1-2/1-3 (1-1만 구현), 순차 잠금 해제 로직
- 공격 이펙트 외 별도 상태이상(슬로우 등) 시스템 — 폭탄타워 5등급의 슬로우 효과는 데이터상 이름만 있고 실제 로직 확인 필요(**미검증**)

## 15. 권장 클래스 구조 (실제 구조 반영)

```text
Game (Singleton)
 ├─ Graphic
 ├─ TimeManager (Singleton)
 └─ SceneManager (Singleton)
     ├─ MainScene    : Scene
     ├─ LobbyScene   : Scene   (스테이지 선택 팝업)
     ├─ EditorScene  : Scene   (리소스 확인용 개발 씬)
     └─ GameScene    : Scene
         ├─ MapSystem        : Grid + TileMap + PathFinder(A* / FindRiskPath)
         ├─ WaveManager       : 라운드/스폰 큐/자동진행
         ├─ EconomyManager    : 골드
         ├─ HealthManager     : 라이프
         ├─ SaveManager       : 세이브/로드
         ├─ PoolManager       : Bloon/Tower/Obstacle/Effect/Projectile 오브젝트 풀
         ├─ TowerController   : 타워 설치/선택/업그레이드/판매 입력 처리
         ├─ ObstacleController: 장애물 설치/선택/판매 입력 처리
         ├─ Tower             : Actor        (DartMonkey/TackShooter/SniperMonkey/BombTower)
         ├─ Bloon             : MovableActor (Red~Ceramic, Special, Boss1/Boss2)
         ├─ BloonPopResolver  : 풍선 터짐 체인 처리
         ├─ Obstacle          : Actor
         ├─ Projectile        : Actor
         └─ Effect            : Actor
```

## 16. 위험 요소와 대응

| 위험 요소 | 대응 방법 | 상태 |
|---|---|---|
| 절차 생성으로 길이 없는 맵 생성 | 생성 직후 A*로 검증하고 실패 시 재생성 | 구현됨(경로가 항상 존재하도록 시작/도착점을 테두리에서 뽑는 방식) |
| 맵이 너무 단순하거나 어려움 | 최소 경로 길이와 미로 복잡도 제한 | 미검증 |
| 4주 내 기능 과다 | 스테이지 1개(1-1), 타워 4종, 풍선 등급 체인+보스 2종을 최소 목표로 고정 | 달성. 목표보다 더 많은 기능(장애물, 세이브/로드, 특수 풍선, 자동진행)까지 추가 구현됨 |
| WinAPI UI 구현 부담 | Direct2D 도형과 텍스트 렌더링 중심으로 단순하게 구현 | 유지 |
| 밸런싱 시간 부족 | 적 체력·속도·보상과 타워 수치를 JSON 데이터 테이블로 관리 | 구현됨(`Resource/Data/*.json`) |

## 17. 완성 기준 대비 현황

- ✅ 스테이지 1개(1-1)에서 유효한 맵과 적 이동 경로가 정상 동작
- ✅ 매 게임마다 다른 유효 맵과 적 이동 경로 생성
- ✅ A* 알고리즘으로 시작점부터 도착점까지 경로 계산 (+ 특수 풍선용 위험도 가중 A* 추가)
- ✅ 적이 계산된 경로를 따라 이동
- ✅ 플레이어가 골드로 타워/장애물 설치
- ✅ 타워가 사거리 내 적을 공격해 제거
- ✅ 적이 도착 지점에 도달하면 라이프 감소
- ✅ 풍선이 터지면 등급 체인(Red~Ceramic)에 따라 하위 풍선으로 이어짐
- ✅ 웨이브(30라운드), 게임 오버/클리어 화면 정상 동작
- ✅ 타워 업그레이드/판매, 장애물, 세이브/로드까지 초안의 "선택 기능" 범위를 넘어 구현 완료
- ⏳ 스테이지 1-2/1-3 확장은 아직 미착수
