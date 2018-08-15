#include "common.h"
#include "renderer.h"
#include "camera.h"
#include "shader.h"

void CShader::Init(CCamera* camera)
{
	m_pCamera = camera;
}

bool CShader::Load()
{
	HRESULT hr;

	do {
		hr = m_pEffect->FindNextValidTechnique(m_hTech, &m_hTechNext);
		if (FAILED(hr))
		{
			return false;	// �G���[

		}

		if (m_hTechNext)
		{
			// �e�N�j�b�N�̃n���h��(m_hTechNext)���擾
			D3DXTECHNIQUE_DESC TechDesc;
			m_pEffect->GetTechniqueDesc(m_hTechNext, &TechDesc); // �e�N�j�b�N�̖��O���擾
			// TechDesc.Name�Ƀe�N�j�b�N���������Ă�
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

		D3DXHANDLE hTVPShader;		// �e�N�j�b�N�uTVPShader�v�̃n���h��
		hTVPShader = m_pEffect->GetTechniqueByName("TVPShader");
		if (hTVPShader == NULL)
		{
			return;	// �e�N�j�b�N�uTVPShader�v��������Ȃ�����
		}

		m_pEffect->SetTechnique(hTVPShader);	// �n���h�����g���ăe�N�j�b�N�uTVPShader�v��I������

		UINT numPass;

		HRESULT hr;

		hr = m_pEffect->Begin(&numPass, 0);

		if (FAILED(hr))
		{
			return;	// �e�N�j�b�N�̊J�n�Ɏ��s
		}

		for (UINT iPass = 0; iPass < numPass; iPass++)
		{
			hr = m_pEffect->BeginPass(iPass);	// iPass�Ԗڂ̃p�X�̎��s���J�n
			if (FAILED(hr))
			{
				break;	// �p�X�̎��s�Ɏ��s
			}

			// ��BeginPass�̌��ID3DXEffect::Set�`���\�b�h���g�����ꍇ�K�v�ɂȂ�
			m_pEffect->CommitChanges(); // (���̃R�[�h��ł͂Ȃ�)

			// �����Ŏ��ۂɃ��b�V����`�悷��


			m_pEffect->EndPass();
		}

		hr = m_pEffect->End();
		if (FAILED(hr))
		{

		}
	}
}
