#include "stdafx.h"
#include "Score.h"
#include <Graphics/TextRenderer.h>
#include <Base/OverlordGame.h>
#include <Content/ContentManager.h>
#include <Components/Components.h>
#include <Graphics/SpriteRenderer.h>
#include <Graphics/SpriteFont.h>
#include <Graphics/TextureData.h>

Score::Score()
{
}


Score::~Score()
{
}

void Score::Initialize(const GameContext & gameContext)
{
	m_ScoreDiamondFont = ContentManager::Load<SpriteFont>(L"./Resources/Font/font.fnt");

	auto sprite = new SpriteComponent(L"./Resources/Textures/Diamond.png");
	AddComponent(sprite);

	sprite->SetPosition({ 30.0f,0.0f });
	sprite->SetVisible(true);


}

void Score::Update(const GameContext & gameContext)
{
}

void Score::Draw(const GameContext & gameContext)
{
	wstringstream scoreDiamonds;
	scoreDiamonds << m_NumDiamonds;

	TextRenderer::GetInstance()->DrawText(m_ScoreDiamondFont, scoreDiamonds.str(), { 0.0f,0.0f }, (XMFLOAT4)Colors::White);

	wstringstream score;
	score << m_Score;
	TextRenderer::GetInstance()->DrawText(m_ScoreDiamondFont, score.str(), { 640.0f,0.0f }, (XMFLOAT4)Colors::White);

	wstringstream lives;
	lives << m_Lives;
	TextRenderer::GetInstance()->DrawText(m_ScoreDiamondFont, lives.str(), { 1260.0f,0.0f }, (XMFLOAT4)Colors::White);
}

void Score::IncreaseScoreDiamonds()
{
	++m_NumDiamonds;
}

void Score::SetScoreDiamonds(int newScore)
{
	m_NumDiamonds = newScore;
}

void Score::IncreaseScore()
{
	m_Score += 100;
}

void Score::SetScore(int newScore)
{
	m_Score = newScore;
}

void Score::DecreaseLives()
{
	--m_Lives;
}

void Score::SetLives(int newLives)
{
	m_Lives = newLives;
}
