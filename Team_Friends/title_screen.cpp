//=============================================================================
// 
//  �^�C�g����ʏ��� [title_screen.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "title_screen.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object2D.h"
#include "calculation.h"
#include "titleslash.h"
#include "input.h"
#include "titleslash_endress.h"

//==========================================================================
// �}�N����`
//==========================================================================
#define WIDTH		(640.0f)	// ����
#define HEIGHT		(360.0f)	// �c��
#define ALPHATIME	(60)		// �s�����x�X�V�̎���
#define LOGOMOVE_TIME	(180)	// ���S�ړ��̎���
#define SLASH_TIME		(60)	// �a���̎���
#define SLASH_MOVETIME	(8)		// �a���̈ړ�����
#define LOGO_POSITION	(D3DXVECTOR3(640.0f, 200.0f, 0.0f))
#define LOGOSIZE_MULTIPLY	(0.55f)
#define CHANGE_TIME		(40)

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
const char *CTitleScreen::m_apTextureFile[VTX_LOGO_MAX] =			// �e�N�X�`���̃t�@�C��
{
	NULL,
	"data\\TEXTURE\\titlelogo_03.png",
	"data\\TEXTURE\\titlelogo_02.png",
	"data\\TEXTURE\\titlelogo_02.png",
	"data\\TEXTURE\\titlelogo_01.png",
	"data\\TEXTURE\\titlelogo_01.png",
};

const char *CTitleScreen::m_apTextureFile_Select[VTXSELECT_MAX] =	// �e�N�X�`���̃t�@�C��
{
	"data\\TEXTURE\\titlelogo_08.png",
};

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CTitleScreen::CTitleScreen(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	memset(&m_pObj2D[0], NULL, sizeof(m_pObj2D));				// �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	memset(&m_pSelect2D[0], NULL, sizeof(m_pSelect2D));			// �I�����̃I�u�W�F�N�g
	memset(&m_nTexIdx[0], 0, sizeof(m_nTexIdx));				// �e�N�X�`���̃C���f�b�N�X�ԍ�
	memset(&m_nTexIdx_Select[0], 0, sizeof(m_nTexIdx_Select));	// �e�N�X�`���̃C���f�b�N�X�ԍ�
	m_nCntAlpha = 0;		// �s�����x�̃J�E���^�[
	m_nCntLogo = 0;		// ���S�ړ��̃J�E���g
	m_bStick = false;		// �X�e�B�b�N�̔���
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CTitleScreen::~CTitleScreen()
{

}

//==========================================================================
// ��������
//==========================================================================
CTitleScreen *CTitleScreen::Create(void)
{
	// �����p�̃I�u�W�F�N�g
	CTitleScreen *pTitleScreen = NULL;

	if (pTitleScreen == NULL)
	{// NULL��������

		// �������̊m��
		pTitleScreen = DEBUG_NEW CTitleScreen;

		if (pTitleScreen != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// ����������
			pTitleScreen->Init();
		}

		return pTitleScreen;
	}

	return NULL;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CTitleScreen::Init(void)
{
	// ��ނ̐ݒ�
	SetType(TYPE_OBJECT2D);

	for (int nCntSelect = 0; nCntSelect < VTX_LOGO_MAX; nCntSelect++)
	{
		// ��������
		m_pObj2D[nCntSelect] = CObject2D::Create(8);

		// ��ނ̐ݒ�
		m_pObj2D[nCntSelect]->SetType(TYPE_OBJECT2D);

		// �e�N�X�`���̊��蓖��
		m_nTexIdx[nCntSelect] = CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile[nCntSelect]);

		// �e�N�X�`���̊��蓖��
		m_pObj2D[nCntSelect]->BindTexture(m_nTexIdx[nCntSelect]);

		D3DXVECTOR2 size;
		// �e��ϐ��̏�����
		switch (nCntSelect)
		{
		case VTX_BLACK:
			// �T�C�Y�擾
			m_pObj2D[nCntSelect]->SetSize(D3DXVECTOR2(640.0f, 360.0f));	// �T�C�Y
			m_pObj2D[nCntSelect]->SetPosition(D3DXVECTOR3(640.0f, 360.0f, 0.0f));	// �ʒu
			m_pObj2D[nCntSelect]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));	// �F
			break;

		case VTX_LOGO:
			// �T�C�Y�擾
			size = CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx[nCntSelect]);
			m_pObj2D[nCntSelect]->SetSize(size * LOGOSIZE_MULTIPLY);	// �T�C�Y
			m_pObj2D[nCntSelect]->SetPosition(LOGO_POSITION);	// �ʒu
			break;

		case VTX_LOGOALPHA1:
			// �T�C�Y�擾
			size = CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx[nCntSelect]);
			m_pObj2D[nCntSelect]->SetSize(size * LOGOSIZE_MULTIPLY);	// �T�C�Y
			m_pObj2D[nCntSelect]->SetPosition(LOGO_POSITION);	// �ʒu
			m_pObj2D[nCntSelect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �F
			break;

		case VTX_LOGOALPHA2:
			// �T�C�Y�擾
			size = CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx[nCntSelect]);
			m_pObj2D[nCntSelect]->SetSize(size * LOGOSIZE_MULTIPLY);	// �T�C�Y
			m_pObj2D[nCntSelect]->SetPosition(LOGO_POSITION);	// �ʒu
			m_pObj2D[nCntSelect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �F
			break;

		case VTX_LOGOPERFECT:
			// �T�C�Y�擾
			size = CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx[nCntSelect]);
			m_pObj2D[nCntSelect]->SetSize(size * LOGOSIZE_MULTIPLY);	// �T�C�Y
			m_pObj2D[nCntSelect]->SetPosition(LOGO_POSITION);	// �ʒu
			m_pObj2D[nCntSelect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �F
			break;

		case VTX_LOGOPERFECTALPHA:
			// �T�C�Y�擾
			size = CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx[nCntSelect]);
			m_pObj2D[nCntSelect]->SetSize(size * LOGOSIZE_MULTIPLY);	// �T�C�Y
			m_pObj2D[nCntSelect]->SetPosition(LOGO_POSITION);	// �ʒu
			m_pObj2D[nCntSelect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �F
			break;
		}
	}

	for (int nCntSelect = 0; nCntSelect < VTXSELECT_MAX; nCntSelect++)
	{
		// ��������
		m_pSelect2D[nCntSelect] = CObject2D::Create(7);

		// ��ނ̐ݒ�
		m_pSelect2D[nCntSelect]->SetType(TYPE_OBJECT2D);

		// �e�N�X�`���̊��蓖��
		m_nTexIdx_Select[nCntSelect] = CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile_Select[nCntSelect]);

		// �e�N�X�`���̊��蓖��
		m_pSelect2D[nCntSelect]->BindTexture(m_nTexIdx_Select[nCntSelect]);

		// �e��ϐ��̏�����
		D3DXVECTOR2 size;
		switch (nCntSelect)
		{
		case VTXSELECT_SELECTSTART:

			// �T�C�Y�擾
			size = CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx_Select[nCntSelect]);
			m_pSelect2D[nCntSelect]->SetSize(D3DXVECTOR2(size.x * 0.4f, size.y * 0.4f));	// �T�C�Y
			m_pSelect2D[nCntSelect]->SetPosition(D3DXVECTOR3(640.0f, 550.0f, 0.0f));	// �ʒu
			break;
		}
	}

	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CTitleScreen::Uninit(void)
{
	for (int nCntSelect = 0; nCntSelect < VTX_LOGO_MAX; nCntSelect++)
	{
		if (m_pObj2D[nCntSelect] != NULL)
		{// NULL����Ȃ�������

			// �I������
			m_pObj2D[nCntSelect] = NULL;
		}
	}

	for (int nCntSelect = 0; nCntSelect < VTXSELECT_MAX; nCntSelect++)
	{
		if (m_pSelect2D[nCntSelect] != NULL)
		{// NULL����Ȃ�������

			// �I������
			m_pSelect2D[nCntSelect] = NULL;
		}
	}

	// ���폜
	Release();
}

//==========================================================================
// �X�V����
//==========================================================================
void CTitleScreen::Update(void)
{

	// �a���X�V
	UpdateSlash();

	for (int nCntSelect = 0; nCntSelect < VTX_LOGO_MAX; nCntSelect++)
	{
		if (m_pObj2D[nCntSelect] == NULL)
		{// NULL��������
			continue;
		}

		switch (nCntSelect)
		{
		case VTX_LOGO:
			// ���S�̍X�V����
			UpdateLogo(nCntSelect);
			break;
		}

		// ���_���ݒ�
		m_pObj2D[nCntSelect]->SetVtx();
	}

	for (int nCntSelect = 0; nCntSelect < VTXSELECT_MAX; nCntSelect++)
	{
		if (m_pSelect2D[nCntSelect] == NULL)
		{// NULL��������
			continue;
		}

		switch (nCntSelect)
		{
		case VTXSELECT_SELECTSTART:
			// �I�����̍X�V����
			UpdateSelect(nCntSelect);
			break;
		}

		// ���_���ݒ�
		m_pSelect2D[nCntSelect]->SetVtx();
	}
}

//==========================================================================
// �a���X�V
//==========================================================================
void CTitleScreen::UpdateSlash()
{
	// ���S�̃J�E���^�[���Z
	m_nCntLogo++;

	if (m_nCntLogo >= SLASH_TIME && m_nCntLogo <= SLASH_TIME + CHANGE_TIME)
	{// �a���̎��Ԓ�������

		if (m_nCntLogo == SLASH_TIME)
		{
			// �e�N�X�`�����擾
			CTexture *pTexture = CManager::GetInstance()->GetTexture();
			int nTex = pTexture->Regist("data\\TEXTURE\\title_slash.png");

			// �a������
			CTitleSlash::Create(LOGO_POSITION);

			for (int nCntSelect = 0; nCntSelect < VTX_LOGO_MAX; nCntSelect++)
			{
				if (m_pObj2D[nCntSelect] == NULL)
				{// NULL��������
					continue;
				}

				if (nCntSelect == VTX_LOGOALPHA1 ||
					nCntSelect == VTX_LOGOALPHA2)
				{
					m_pObj2D[nCntSelect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
				}
			}
		}

		for (int nCntSelect = 0; nCntSelect < VTX_LOGO_MAX; nCntSelect++)
		{
			if (m_pObj2D[nCntSelect] == NULL)
			{// NULL��������
				continue;
			}

			// �F�擾
			D3DXCOLOR col = m_pObj2D[nCntSelect]->GetColor();
			D3DXVECTOR2 size = m_pObj2D[nCntSelect]->GetSize();

			if (nCntSelect == VTX_LOGOALPHA1 ||
				nCntSelect == VTX_LOGOALPHA2)
			{
				// �����̏���
				UpdateSlashAlpha(nCntSelect);
				continue;
			}
			else if (nCntSelect == VTX_BLACK)
			{
				// ����
				int nCntTime = m_nCntLogo - SLASH_TIME;

				// �F
				col.a = (1.0f - ((float)nCntTime / (float)CHANGE_TIME));
			}
			else if (nCntSelect == VTX_LOGO)
			{
				// ����
				int nCntTime = m_nCntLogo - SLASH_TIME;

				// �F
				col.a = (1.0f - ((float)nCntTime / (float)CHANGE_TIME));
			}
			else if (nCntSelect == VTX_LOGOPERFECT)
			{
				// ����
				int nCntTime = m_nCntLogo - SLASH_TIME;

				// �F
				col.a = (float)nCntTime / (float)CHANGE_TIME;
			}
			else if (nCntSelect == VTX_LOGOPERFECTALPHA)
			{
				// ����
				int nCntTime = m_nCntLogo - SLASH_TIME;
				D3DXVECTOR2 DestSize = CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx[nCntSelect]) * 1.2f;

				size += (DestSize - size) * 0.1f;

				// �F
				col.a = 0.5f * (1.0f - ((float)nCntTime / (float)CHANGE_TIME));
			}

			// �F�ݒ�
			m_pObj2D[nCntSelect]->SetColor(col);
			m_pObj2D[nCntSelect]->SetSize(size);
		}
	}

	if (m_nCntLogo > SLASH_TIME + CHANGE_TIME)
	{// �a���̎��Ԓ�������

		// �Q�[���p�b�h���擾
		CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

		if (pInputGamepad->GetStickPositionRatioR(0).y <= 0.2f && pInputGamepad->GetStickPositionRatioR(0).y >= -0.2f &&
			pInputGamepad->GetStickPositionRatioR(0).x <= 0.2f && pInputGamepad->GetStickPositionRatioR(0).x >= -0.2f)
		{// ����������
			// �X�e�B�b�N�|�����Ԃɂ���
			m_bStick = false;
		}

		if (m_bStick == false &&
			(pInputGamepad->GetStickPositionRatioR(0).y >= 0.5f || pInputGamepad->GetStickPositionRatioR(0).y <= -0.5f ||
				pInputGamepad->GetStickPositionRatioR(0).x >= 0.5f || pInputGamepad->GetStickPositionRatioR(0).x <= -0.5f))
		{// �U��

			// �X�e�B�b�N�|��������
			m_bStick = true;
			CTitleSlashEndress::Create();
		}
	}
}

//==========================================================================
// �����̎a���X�V
//==========================================================================
void CTitleScreen::UpdateSlashAlpha(int nCntSelect)
{
	// ���擾
	D3DXCOLOR col = m_pObj2D[nCntSelect]->GetColor();
	D3DXVECTOR3 pos = m_pObj2D[nCntSelect]->GetPosition();

	D3DXVECTOR3 posDest[VTX_LOGO_MAX];
	posDest[VTX_LOGOALPHA1] = D3DXVECTOR3(640.0f + 250.0f, LOGO_POSITION.y - 120.0f, 0.0f);
	posDest[VTX_LOGOALPHA2] = D3DXVECTOR3(640.0f - 250.0f, LOGO_POSITION.y + 120.0f, 0.0f);

	// ����
	int nCntTime = m_nCntLogo - SLASH_TIME;

	// �F
	col.a = 0.3f * (1.0f - ((float)nCntTime / (float)CHANGE_TIME));

	// �ʒu�X�V
	pos += (posDest[nCntSelect] - pos) * 0.1f;

	// ���ݒ�
	m_pObj2D[nCntSelect]->SetColor(col);
	m_pObj2D[nCntSelect]->SetPosition(pos);

}

//==========================================================================
// ���S�̍X�V����
//==========================================================================
void CTitleScreen::UpdateLogo(int nCntSelect)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = m_pObj2D[nCntSelect]->GetPosition();


	// �ʒu�ݒ�
	m_pObj2D[nCntSelect]->SetPosition(pos);
}

//==========================================================================
// �I�����̍X�V����
//==========================================================================
void CTitleScreen::UpdateSelect(int nCntSelect)
{
	// �F�擾
	D3DXCOLOR col = m_pSelect2D[nCntSelect]->GetColor();

	// �s�����x�X�V
	CuadricCurveComp(col.a, ALPHATIME, 0.1f, 1.0f, m_nCntAlpha);

	// �F�ݒ�
	m_pSelect2D[nCntSelect]->SetColor(col);
}

//==========================================================================
// �`�揈��
//==========================================================================
void CTitleScreen::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	for (int nCntSelect = 0; nCntSelect < VTX_LOGO_MAX; nCntSelect++)
	{
		// �`�揈��
		m_pObj2D[nCntSelect]->Draw();
	}

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

