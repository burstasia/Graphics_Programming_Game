#pragma once
class MeshFilter;
class ShadowMapMaterial;
class RenderTarget;

class ShadowMapRenderer
{
public:
	ShadowMapRenderer();
	~ShadowMapRenderer();

	void Begin(const GameContext& gameContext);
	void Draw(const GameContext& gameContext, MeshFilter* pMeshFilter, XMFLOAT4X4 world);
	void End(const GameContext& gameContext);
	XMFLOAT3 GetLightDirection();
	XMFLOAT4X4 GetLightVP();
	ShadowMapMaterial* GetMaterial();
	ID3D11ShaderResourceView* GetShadowMap();
	void Init(const GameContext& gameContext);
	void SetLight(XMFLOAT3 position, XMFLOAT3 direction);

private:

	bool m_IsInitialized;
	XMFLOAT3 m_LightDirection;
	XMFLOAT3 m_LightPosition;
	XMFLOAT4X4 m_LightVP;
	ShadowMapMaterial* m_pShadowMat;
	RenderTarget* m_pShadowRT;
	const float m_Size;

	ShadowMapRenderer& operator =(const ShadowMapRenderer& yRef);
	ShadowMapRenderer(const ShadowMapRenderer& yRef);
};

