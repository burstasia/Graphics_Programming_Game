#pragma once
#include "..\Scenegraph\GameObject.h"

class BezierMaterial;
class MaterialComponentBezier;
class SpherePrefab;

class BezierPrefab: public GameObject
{
public:
	BezierPrefab(XMFLOAT3 P0, XMFLOAT3 P1, XMFLOAT3 P2, XMFLOAT3 P3, 
		float radius, int segs, int circleSides);
	~BezierPrefab();

	void IncreaseSegments(const GameContext& gameContext);
	void DecreaseSegments(const GameContext& gameContext);

	void SetActive(bool isActive);
	bool GetIsActive();

	void SwitchActivePoint();

	void MoveX(float value);
	void MoveY(float value);
	void MoveZ(float value);

protected:
	virtual void Update(const GameContext& gameContext) override;
	virtual void Draw(const GameContext& gameContext) override;
	virtual void Initialize(const GameContext& gameContext) override;

private:

	float m_Radius;
	int m_SegmentCount;
	int m_CircleSides;
	bool m_IsLeft;
	bool m_IsRight;

	XMFLOAT3 m_P0;
	XMFLOAT3 m_P1;
	XMFLOAT3 m_P2;
	XMFLOAT3 m_P3;

	SpherePrefab *m_pP0_Sphere;
	SpherePrefab *m_pP1_Sphere;
	SpherePrefab *m_pP2_Sphere;
	SpherePrefab *m_pP3_Sphere;

	XMFLOAT3 m_ScaleBalls{ 0.25f, 0.25f, 0.25f };

	XMFLOAT4 m_ActivePointColour{1.0f,0.0f,0.0f,1.0f};
	XMFLOAT4 m_InactiveBezierColour{0.0f,0.0f,1.0f,1.0f};
	XMFLOAT4 m_InactivePointColour{ 1.0f,1.0f,1.0f,1.0f };

	bool m_IsActiveBezier;

	int m_ActivePoint;

	MaterialComponentBezier* m_pBezierMatComponentLeftTrack;
	MaterialComponentBezier* m_pBezierMatComponentRightTrack;
	MaterialComponentBezier* m_pBezierMatComponentBeams;
	MaterialComponentBezier* m_pBezierMatComponentSupportsLeft;
	MaterialComponentBezier* m_pBezierMatComponentSupportsRight;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	BezierPrefab(const BezierPrefab& yRef);
	BezierPrefab& operator=(const BezierPrefab& yRef);

};

