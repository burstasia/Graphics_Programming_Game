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

	void IncreaseScore();
	void SetScore(int newScore);

	void DecreaseLives();
	void SetLives(int newLives);

private:
	SpriteFont * m_ScoreDiamondFont = nullptr;
	
	int m_NumDiamonds = 0;
	int m_Score = 0;
	int m_Lives = 10;
};

