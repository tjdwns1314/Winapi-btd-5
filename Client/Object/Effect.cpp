#include "pch.h"
#include "Effect.h"
#include "ResourceManager.h"

void Effect::Init()
{
	Super::Init();
	SetActorType(ActorType::Effect);
	SetLayer(RenderLayer::Effect);

	ResourceManager& res = ResourceManager::GetInstance();
	_image = &res.GetImage(L"Resource\\Sprite\\InGame.png");
	SpriteAtlas& atlas = res.GetAtlas(L"Resource\\Sprite\\InGame.xml");

	const EffectData& data = GetEffectData(_type);
	_frameTime = data.frameTime;

	_frames.clear();
	for (const string& name : data.frameNames)
		_frames.push_back(atlas.GetCell(name));

	const CellInfo* firstCell = _frames.empty() ? nullptr : _frames[0];
	const float scale = (firstCell != nullptr) ? static_cast<float>(BLOCK_SIZE) / firstCell->w * data.scale : data.scale;
	SetScale(Vector(scale, scale));

	// 풀에서 재사용될 때 이전 경과 시간이 남지 않도록 초기화
	_elapsed = 0.f;
}

void Effect::Update(float deltaTime)
{
	Super::Update(deltaTime);

	_elapsed += deltaTime;
	if (_elapsed >= _frameTime * static_cast<float>(_frames.size()))
		SetPendingKill();
}

void Effect::Render(Graphic& graphic)
{
	Super::Render(graphic);

	if (_image == nullptr || _frames.empty())
		return;

	const int32 frameIndex = std::clamp(static_cast<int32>(_elapsed / _frameTime), 0, static_cast<int32>(_frames.size()) - 1);
	const CellInfo* cell = _frames[frameIndex];
	if (cell == nullptr)
		return;

	const Vector pos = GetPos();
	const Vector scale = GetScale();
	_image->DrawSprite(graphic, pos.x, pos.y, *cell, scale.x);
}
