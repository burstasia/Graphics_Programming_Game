#pragma once
#include "BaseComponent.h"

class TextureData;

class SpriteComponent : public BaseComponent
{
public:
	SpriteComponent(const wstring& spriteAsset, XMFLOAT2 pivot = XMFLOAT2(0,0), XMFLOAT4 color = (XMFLOAT4)Colors::White);
	~SpriteComponent(void);

	XMFLOAT2 GetPivot() const { return m_Pivot; }
	XMFLOAT4 GetColor() const { return m_Color; }

	void SetPivot(XMFLOAT2 pivot) { m_Pivot = pivot; }
	void SetColor(XMFLOAT4 color) { m_Color = color; }
	void SetTexture(const wstring& spriteAsset);
	void SetVisible(bool isVisible) { m_IsVisible = isVisible; }
	void SetPosition(XMFLOAT2 position) { m_Pos = position; }
	void Translate(XMFLOAT2 delta) { m_Pos.x += delta.x; m_Pos.y += delta.y; }
	XMFLOAT2 GetPos() { return m_Pos; }

protected:
	virtual void Initialize(const GameContext& gameContext);
	virtual void Update(const GameContext& gameContext);
	virtual void Draw(const GameContext& gameContext);

private:

	TextureData* m_pTexture;
	wstring m_SpriteAsset;
	XMFLOAT2 m_Pivot;
	XMFLOAT4 m_Color;
	XMFLOAT2 m_Pos = {0.0f,0.0f};

	bool m_IsVisible;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	SpriteComponent(const SpriteComponent& obj);
	SpriteComponent& operator=(const SpriteComponent& obj);
};

