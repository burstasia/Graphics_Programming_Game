#pragma once
#include "Scenegraph/GameScene.h"

class BezierPrefab;

class BezierScene : public GameScene
{
public:
	BezierScene();
	virtual ~BezierScene();

	enum InputActions : UINT
	{
		INCREASE_SEGS,
		DECREASE_SEGS,
		SWITCH_BEZIERS,
		SWITCH_ACTIVE_POINT,
		MOVE_X_POS,
		MOVE_X_NEG,
		MOVE_Y_POS,
		MOVE_Y_NEG,
		MOVE_Z_POS,
		MOVE_Z_NEG
	};


protected:

	virtual void Initialize(const GameContext& gameContext);
	virtual void Update(const GameContext& gameContext);
	virtual void Draw(const GameContext& gameContext);

private:
	BezierPrefab * m_pBezier_01;
	BezierPrefab * m_pBezier_02;
	//BezierPrefab * m_pBezier_03;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	BezierScene(const BezierScene &obj);
	BezierScene& operator=(const BezierScene& obj);
};

