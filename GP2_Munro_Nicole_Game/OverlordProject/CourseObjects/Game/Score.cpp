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
	m_ScoreFont = ContentManager::Load<SpriteFont>(L"./Resources/Font/font.fnt");

}

void Score::Update(const GameContext & gameContext)
{
}

void Score::Draw(const GameContext & gameContext)
{
	wstringstream score;

	score << m_NumDiamonds;

	TextRenderer::GetInstance()->DrawText(m_ScoreFont, score.str(), { 0.0f,0.0f }, (XMFLOAT4)Colors::White);
}

void Score::IncreaseScoreDiamonds()
{
	++m_NumDiamonds;
}

void Score::SetScoreDiamonds(int newScore)
{
	m_NumDiamonds = newScore;
}
