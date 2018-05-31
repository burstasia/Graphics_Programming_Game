#pragma once
class BezierMaterial;

class MaterialComponentBezier : public BaseComponent
{
public:
	MaterialComponentBezier(XMFLOAT3 P0, XMFLOAT3 P1, XMFLOAT3 P2, XMFLOAT3 P3,
		float radius, int segs, int circleSides, bool left, bool right, bool crossBeams, bool leftSupport, bool rightSupport);
	~MaterialComponentBezier();

	
protected:
	friend class BezierPrefab;

	void Update(const GameContext& gameContext) override;
	void Draw(const GameContext& gameContext) override;
	void Initialize(const GameContext& gameContext) override;

	BezierMaterial *m_pBezierMaterialLeft;

	void UpdateBezierPoints(XMFLOAT3 P0, XMFLOAT3 P1, XMFLOAT3 P2, XMFLOAT3 P3);
private:
	void LoadEffect(const GameContext& gameContext);
	void InitializeBuffer(const GameContext& gameContext);
	void UpdateBuffer(/*const GameContext& gameContext*/);

	ID3D11Buffer * m_pVertexBuffer;

	std::vector<VertexBezier> m_Verts;
	ID3DX11EffectTechnique* m_pTechnique;
	ID3D11InputLayout* m_pInputLayout;
	static ID3DX11EffectMatrixVariable *m_pWorldVar, *m_pWvpVar;

	

	UINT m_MaterialID;
	bool m_MaterialSet;

};

