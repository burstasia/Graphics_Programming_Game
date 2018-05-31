#pragma once
#include "../Graphics/Material.h"
class TextureData;

class BezierMaterial : public Material
{
public:
	BezierMaterial(float radius, int numCircleSides, int segmentCount, bool isLeft, bool isRight
		, bool isCrossBeams, bool leftSupport, bool rightSupport);
	~BezierMaterial();

	int GetNumSegments();
	void SetNumSegments(int segments);

	int GetCircleSides();
	void SetCircleSides(int circleSides);

	float GetRadius();
	void SetRadius(float radius);

	bool GetLeft();
	void SetLeft(bool isLeft);

	bool GetRight();
	void SetRight(bool isRight);

	bool GetCrossBeams();
	void SetCrossBeams(bool isCrossBeams);

protected:
	friend class MaterialComponentBezier;

	virtual void LoadEffectVariables() override;
	virtual void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent) override;


	float m_Radius;
	ID3DX11EffectScalarVariable* m_pRadius;

	int m_Segments;
	ID3DX11EffectScalarVariable* m_pSegments;

	int m_CircleSides;
	ID3DX11EffectScalarVariable* m_pCircleSides;

	bool m_IsRight;
	ID3DX11EffectScalarVariable* m_pIsRight;

	bool m_IsLeft;
	ID3DX11EffectScalarVariable* m_pIsLeft;

	bool m_IsCrossBeams;
	ID3DX11EffectScalarVariable* m_pIsCrossBeams;

	bool m_IsLeftSupport;
	ID3DX11EffectScalarVariable* m_pIsLeftSupport;

	bool m_IsRightSupport;
	ID3DX11EffectScalarVariable* m_pIsRightSupport;
private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	BezierMaterial(const BezierMaterial &obj);
	BezierMaterial& operator=(const BezierMaterial& obj);
};

