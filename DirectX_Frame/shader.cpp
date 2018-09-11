#include "common.h"
#include "renderer.h"
#include "camera.h"
#include "texture.h"
#include "shader.h"
#include "box.h"

CBox box;

void CShader::Init(CCamera* camera)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	m_pCamera = camera;

	box.Init(1, 1, 1, TEX_ID_FIELD001);

	D3DXCreateEffectFromFile(
		pDevice,
		"shader.fx",
		NULL,
		NULL,
		D3DXSHADER_DEBUG,
		NULL,
		&m_pEffect,
		NULL
	);
}

void CShader::Uninit()
{
	box.Uninit();

	if (m_pEffect)
	{
		m_pEffect->Release();
	}

}

bool CShader::Load()
{
	HRESULT hr;

	do {
		hr = m_pEffect->FindNextValidTechnique(m_hTech, &m_hTechNext);
		if (FAILED(hr))
		{
			return false;	// エラー
		}

		if (m_hTechNext)
		{
			// テクニックのハンドル(m_hTechNext)を取得
			D3DXTECHNIQUE_DESC TechDesc;
			m_pEffect->GetTechniqueDesc(m_hTechNext, &TechDesc); // テクニックの名前を取得
																 // TechDesc.Nameにテクニック名が入ってる
		}
		m_hTech = m_hTechNext;
	} while (m_hTech != NULL);
}

void CShader::Draw()
{
	if (m_pCamera != NULL)
	{
		m_pEffect->SetMatrix("World", &m_World);
		m_pEffect->SetMatrix("View", &m_pCamera->GetView());
		m_pEffect->SetMatrix("Proj", &m_pCamera->GetProjection());

		D3DXHANDLE hTVPShader;		// テクニック「TVPShader」のハンドル
		hTVPShader = m_pEffect->GetTechniqueByName("TVPShader");
		if (hTVPShader == NULL)
		{
			return;	// テクニック「TVPShader」が見つからなかった
		}

		m_pEffect->SetTechnique(hTVPShader);	// ハンドルを使ってテクニック「TVPShader」を選択する

		UINT numPass;

		HRESULT hr;

		hr = m_pEffect->Begin(&numPass, 0);

		if (FAILED(hr))
		{
			MessageBox(NULL, "テクニックの開始に失敗しました", "エラー", MB_OK);
			return;	// テクニックの開始に失敗
		}

		for (UINT iPass = 0; iPass < numPass; iPass++)
		{
			hr = m_pEffect->BeginPass(iPass);	// iPass番目のパスの実行を開始
			if (FAILED(hr))
			{
				MessageBox(NULL, "パスの実行に失敗しました", "エラー", MB_OK);
				break;	// パスの実行に失敗
			}

			// ↓BeginPassの後でID3DXEffect::Set～メソッドを使った場合必要になる
			// m_pEffect->CommitChanges(); // (このコード例ではない)
			box.Draw(m_World);

			// ここで実際にメッシュを描画する
			m_pEffect->EndPass();
		}

		hr = m_pEffect->End();
		if (FAILED(hr))
		{

		}
	}
}
