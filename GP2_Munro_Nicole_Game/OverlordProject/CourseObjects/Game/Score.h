#pragma once
#include "Scenegraph/GameObject.h"

class SpriteFont;
class TextureData;

class Score final : public GameObject
{
public:
	Score();
	~Score();

	virtual void Initialize(const GameContext& gameContext);
	virtual void Update(const GameContext& gameContext);
	virtual void Draw(const GameContext& gameContext);

	void IncreaseScoreDiamonds();
	void SetScoreDiamonds(int newScore);
private:
	SpriteFont * m_ScoreFont = nullptr;

	int m_NumDiamonds = 0;
};

