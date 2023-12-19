//=============================================================================
// 
//  �`���[�g���A���e�L�X�g���� [tutorialtext.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "tutorialtext.h"
#include "tutorial.h"
#include "tutorialstep.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object2D.h"
#include "calculation.h"

//==========================================================================
// �}�N����`
//==========================================================================
#define WIDTH		(640.0f)	// ����
#define HEIGHT		(360.0f)	// �c��
#define ALPHATIME	(60)		// �s�����x�X�V�̎���
#define LOGOMOVE_TIME	(180)	// ���S�ړ��̎���
#define LOGO_POSITION	(D3DXVECTOR3(640.0f, 160.0f, 0.0f))
#define TEXT_POSITION	(D3DXVECTOR3(640.0f, 500.0f, 0.0f))
#define ALPHA_MOVE	(0.02f)	// �s�����x�X�V��

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
const char *CTutorialText::m_apTextureFile[TEX_MAX] =	// �e�N�X�`���̃t�@�C��
{
	"data\\TEXTURE\\tutorialtalk\\window_01.png",
	"data\\TEXTURE\\tutorialtalk\\text_00.png",
	"data\\TEXTURE\\tutorialtalk\\text_01.png",
	"data\\TEXTURE\\tutorialtalk\\text_02.png",
	"data\\TEXTURE\\tutorialtalk\\text_03.png",
	"data\\TEXTURE\\tutorialtalk\\text_04.png",
	"data\\TEXTURE\\tutorialtalk\\text_05.png",
	"data\\TEXTURE\\tutorialtalk\\skip_01.png",
};

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CTutorialText::CTutorialText(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	memset(&m_nTexIdx[0], 0, sizeof(m_nTexIdx));	// �e�N�X�`���̃C���f�b�N�X�ԍ�
	memset(&m_pObj2D[0], NULL, sizeof(m_pObj2D));	// �I�u�W�F�N�g2D�̃I�u�W�F�N�g
	m_nCntMoving = 0;	// �ړ����Ă�J�E���^�[
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CTutorialText::~CTutorialText()
{

}

//==========================================================================
// ��������
//==========================================================================
CTutorialText *CTutorialText::Create(void)
{
	// �����p�̃I�u�W�F�N�g
	CTutorialText *pTitleScreen = nullptr;

	if (pTitleScreen == nullptr)
	{// NULL��������

		// �������̊m��
		pTitleScreen = DEBUG_NEW CTutorialText;

		if (pTitleScreen != nullptr)
		{// �������̊m�ۂ��o���Ă�����

			// ����������
			pTitleScreen->Init();
		}

		return pTitleScreen;
	}

	return nullptr;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CTutorialText::Init(void)
{
	// ��ނ̐ݒ�
	SetType(TYPE_OBJECT2D);

	for (int nCntTex = 0; nCntTex < TEX_MAX; nCntTex++)
	{
		// �e�N�X�`���̊��蓖��
		m_nTexIdx[nCntTex] = CManager::GetInstance()->GetTexture()->Regist(m_apTextureFile[nCntTex]);
	}

	for (int nCntVtx = 0; nCntVtx < VTX_MAX; nCntVtx++)
	{
		// ��������
		m_pObj2D[nCntVtx] = m_pObj2D[nCntVtx]->Create(7);
		m_pObj2D[nCntVtx]->SetType(TYPE_OBJECT2D);

		// �e�N�X�`���̊��蓖��
		D3DXVECTOR2 size;
		switch (nCntVtx)
		{
		case VTX_WINDOW:
			m_pObj2D[nCntVtx]->BindTexture(m_nTexIdx[TEX_WINDOW]);

			// �T�C�Y�擾
			size = CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx[TEX_WINDOW]);
			m_pObj2D[nCntVtx]->SetSize(size * 0.4f);	// �T�C�Y
			m_pObj2D[nCntVtx]->SetPosition(D3DXVECTOR3(640.0f, SCREEN_HEIGHT - m_pObj2D[nCntVtx]->GetSize().y, 0.0f));	// �ʒu
			break;

		case VTX_TEXT:
			m_pObj2D[nCntVtx]->BindTexture(m_nTexIdx[TEX_TEXT_WAIT]);

			// �T�C�Y�擾
			size = CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx[TEX_TEXT_WAIT]);
			m_pObj2D[nCntVtx]->SetSize(size * 0.4f);	// �T�C�Y
			m_pObj2D[nCntVtx]->SetPosition(D3DXVECTOR3(640.0f, SCREEN_HEIGHT - m_pObj2D[nCntVtx]->GetSize().y, 0.0f));	// �ʒu
			break;

		case VTX_SKIP:
			m_pObj2D[nCntVtx]->BindTexture(m_nTexIdx[TEX_SKIP]);

			// �T�C�Y�擾
			size = CManager::GetInstance()->GetTexture()->GetImageSize(m_nTexIdx[TEX_SKIP]);
			m_pObj2D[nCntVtx]->SetSize(size * 0.2f);	// �T�C�Y
			m_pObj2D[nCntVtx]->SetPosition(D3DXVECTOR3(1020.0f, 560.0f, 0.0f));	// �ʒu
			break;
		}
	}

	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CTutorialText::Uninit(void)
{
	for (int i = 0; i < VTX_MAX; i++)
	{
		if (m_pObj2D[i] != nullptr)
		{// NULL����Ȃ�������

			//m_pObj2D[i]->Uninit();
			//delete m_pObj2D[i];
			m_pObj2D[i] = nullptr;
		}
	}

	// ���폜
	Release();
}

//==========================================================================
// �X�V����
//==========================================================================
void CTutorialText::Update(void)
{
	// �e�N�X�`���؂�ւ�
	m_pObj2D[VTX_TEXT]->BindTexture(m_nTexIdx[TEX_TEXT_WAIT + CTutorial::GetStep()->GetNowStep()]);

	// �v���C���[���ړ����Ă锻��
	bool bMoving = CTutorial::IsMovingPlayer();

	// �ړ����Ă�J�E���^�[���Z
	if (bMoving == true)
	{
		m_nCntMoving++;
	}
	else
	{
		m_nCntMoving--;
	}

	// �l�̐��K��
	ValueNormalize(m_nCntMoving, 20, 0);

	for (int nCntVtx = 0; nCntVtx < VTX_MAX; nCntVtx++)
	{
		if (m_pObj2D[nCntVtx] == nullptr)
		{// NULL��������
			continue;
		}

		// �F�擾
		D3DXCOLOR col = m_pObj2D[nCntVtx]->GetColor();

		if (m_nCntMoving >= 20)
		{// �s�����Ă�Ƃ�

			col.a -= ALPHA_MOVE;
		}
		else if(m_nCntMoving <= 0)
		{
			col.a += ALPHA_MOVE;
		}


		// �l�̐��K��
		ValueNormalize(col.a, 1.0f, 0.3f);

		// �F�ݒ�
		m_pObj2D[nCntVtx]->SetColor(col);

		// ���_���ݒ�
		SetVtx(nCntVtx);
	}
}

//==========================================================================
// �`�揈��
//==========================================================================
void CTutorialText::Draw(void)
{
	//// �f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//// �A���t�@�e�X�g��L���ɂ���
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//for (int i = 0; i < VTX_MAX; i++)
	//{
	//	if (m_pObj2D[i] == nullptr)
	//	{// NULL��������
	//		continue;
	//	}

	//	// �`�揈��
	//	m_pObj2D[i]->Draw();
	//}

	//// �A���t�@�e�X�g�𖳌��ɂ���
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==========================================================================
// ���_���ݒ菈��
//==========================================================================
void CTutorialText::SetVtx(void)
{

}

//==========================================================================
// ���_���ݒ菈��
//==========================================================================
void CTutorialText::SetVtx(int nCntSelect)
{
	// ���_�ݒ�
	m_pObj2D[nCntSelect]->SetVtx();
}
