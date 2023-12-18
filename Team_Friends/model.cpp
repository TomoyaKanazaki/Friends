//=============================================================================
// 
//  ���f������ [model.cpp]
//  Author : ���n�Ή�
// 
//=============================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "calculation.h"
#include "texture.h"
#include "Xload.h"

//==========================================================================
// �}�N����`
//==========================================================================

//==========================================================================
// �ÓI�����o�ϐ��錾
//==========================================================================
int CModel::m_nNumAll = 0;	// ����

//==========================================================================
// �R���X�g���N�^
//==========================================================================
CModel::CModel(int nPriority)
{
	D3DXMatrixIdentity(&m_mtxWorld);				// ���[���h�}�g���b�N�X
	m_pos = mylib_const::DEFAULT_VECTOR3;			// �ʒu
	m_posOld = mylib_const::DEFAULT_VECTOR3;		// �O��̈ʒu
	m_posOrigin = mylib_const::DEFAULT_VECTOR3;		// ���̈ʒu
	m_rot = mylib_const::DEFAULT_VECTOR3;			// ����
	m_rotOrigin = mylib_const::DEFAULT_VECTOR3;		// ����
	m_scale = mylib_const::DEFAULT_SCALE;			// �X�P�[��
	m_nIdxXFile = 0;								// X�t�@�C���̃C���f�b�N�X�ԍ�
	m_nIdxTexture = NULL;							// �e�N�X�`���̃C���f�b�N�X�ԍ�
	m_pParent = NULL;								// �e���f���̃|�C���^
	m_nNumAll++;									// �������Z
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
CModel::~CModel()
{

}

//==========================================================================
// X�t�@�C���̃f�[�^���蓖��
//==========================================================================
void CModel::BindXData(int nIdxXFile)
{
	// ��񊄂蓖��
	m_nIdxXFile = nIdxXFile;

	// �e�N�X�`�����蓖��
	BindTexture();
}

//==========================================================================
// �e�N�X�`�����蓖��
//==========================================================================
void CModel::BindTexture(void)
{
	if (m_nIdxTexture != NULL)
	{
		delete[] m_nIdxTexture;
	}

	// X�t�@�C���̃f�[�^�擾
	CXLoad::SXFile *pXData = CScene::GetXLoad()->GetMyObject(m_nIdxXFile);

	// �}�e���A�����������m��
	m_nIdxTexture = DEBUG_NEW int[(int)pXData->dwNumMat];

	// �e�N�X�`���̃C���f�b�N�X�ԍ�
	for (int i = 0; i < (int)pXData->dwNumMat; i++)
	{
		m_nIdxTexture[i] = pXData->nIdxTexture[i];
	}
}

//==========================================================================
// �e�̃}�g���b�N�X�ݒ�
//==========================================================================
void CModel::SetParent(CModel *pModel)
{
	// �e�̃|�C���^��n��
	m_pParent = pModel;
}

//==========================================================================
// ��������
//==========================================================================
CModel *CModel::Create(const char *pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �����p�̃I�u�W�F�N�g
	CModel *pModel = NULL;

	if (pModel == NULL)
	{// NULL��������

		// �������̊m��
		pModel = DEBUG_NEW CModel;

		if (pModel == NULL)
		{// NULL��������

			delete pModel;
			pModel = NULL;
			return NULL;
		}

		if (pModel != NULL)
		{// �������̊m�ۂ��o���Ă�����

			// ����������
			HRESULT hr = pModel->Init(pFileName);

			if (FAILED(hr))
			{// ���s���Ă�����
				return NULL;
			}

			// �ʒu�E����
			pModel->SetPosition(pos);
			pModel->m_posOrigin = pos;
			pModel->SetRotation(rot);
			pModel->SetOriginRotation(rot);
		}

		return pModel;
	}

	return NULL;
}

//==========================================================================
// ����������
//==========================================================================
HRESULT CModel::Init(const char *pFileName)
{
	// X�t�@�C���̃f�[�^�擾
	CXLoad *pXLoad = CScene::GetXLoad();

	// X�t�@�C���̃��[�h
	m_nIdxXFile = pXLoad->XLoad(pFileName);

	// X�t�@�C���̃f�[�^���蓖��
	BindXData(m_nIdxXFile);

	// X�t�@�C���̃f�[�^�擾
	CXLoad::SXFile *pXData = CScene::GetXLoad()->GetMyObject(m_nIdxXFile);

	// �S���_�`�F�b�N
	CheckVtx(GetRotation().y, &pXData->vtxMax, &pXData->vtxMin, pXData->pMesh, pXData->pVtxBuff);

	// �e�N�X�`�����蓖��
	BindTexture();
	return S_OK;
}

//==========================================================================
// �I������
//==========================================================================
void CModel::Uninit(void)
{
	//// �e���f���̃|�C���^
	//if (m_pParent != NULL)
	//{
	//	m_pParent = NULL;
	//}
	if (m_nIdxTexture != NULL)
	{
		delete[] m_nIdxTexture;
	}
}

//==========================================================================
// �X�V����
//==========================================================================
void CModel::Update(void)
{
	// X�t�@�C���̃f�[�^�擾
	CXLoad *pXLoad = CScene::GetXLoad();

	// X�t�@�C���̃f�[�^�擾
	CXLoad::SXFile *pXData = CScene::GetXLoad()->GetMyObject(m_nIdxXFile);

	// �S���_�`�F�b�N
	CheckVtx(GetRotation().y, &pXData->vtxMax, &pXData->vtxMin, pXData->pMesh, pXData->pVtxBuff);
}

//==========================================================================
// ���[���h�}�g���b�N�X�v�Z
//==========================================================================
void CModel::CalWorldMtx(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxRotOrigin;	// �v�Z�p�}�g���b�N�X�錾
	D3DXMATRIX mtxnParent;			// �e�̃}�g���b�N�X

	bool bScale = false;

	// �e�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxRotOrigin);
	D3DXMatrixIdentity(&mtxnParent);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �X�P�[���𔽉f����
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// ���̌����𔽉f����
	D3DXMatrixRotationYawPitchRoll(&mtxRotOrigin, m_rotOrigin.y, m_rotOrigin.x, m_rotOrigin.z);

	// �����𔽉f����
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotOrigin);

	// �ʒu�𔽉f����
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// �e�̃}�g���b�N�X�Ɗ|�����킹��
	if (m_pParent == NULL)
	{// �������e�������ꍇ

		// �ŐV�̃}�g���b�N�X��n��(DirectX���o���Ă������)
		pDevice->GetTransform(D3DTS_WORLD, &mtxnParent);
	}
	else
	{// �e������ꍇ

		// �e�̃}�g���b�N�X��n��
		mtxnParent = m_pParent->GetWorldMtx();

		D3DXVECTOR3 scaleVector;

		// �}�g���b�N�X����X�P�[�����𒊏o
		scaleVector.x = D3DXVec3Length(&D3DXVECTOR3(mtxnParent._11, mtxnParent._12, mtxnParent._13));
		scaleVector.y = D3DXVec3Length(&D3DXVECTOR3(mtxnParent._21, mtxnParent._22, mtxnParent._23));
		scaleVector.z = D3DXVec3Length(&D3DXVECTOR3(mtxnParent._31, mtxnParent._32, mtxnParent._33));
		if (scaleVector != D3DXVECTOR3(1.0f, 1.0f, 1.0f))
		{
			bScale = true;
		}
	}

	// �����ɐe�̃��[���h�}�g���b�N�X���|����
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxnParent);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	if (m_scale != D3DXVECTOR3(1.0f, 1.0f, 1.0f))
	{// �����ł��Ⴄ�ꍇ

		bScale = true;
	}

	if (bScale)
	{
		// �������K����ON�ɂ���
		pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	}

}

//==========================================================================
// �`�揈��
//==========================================================================
void CModel::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X�錾
	D3DXMATRIX mtxRotOrigin;		// �v�Z�p�}�g���b�N�X�錾
	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxnParent;			// �e�̌v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̌v�Z����
	CalWorldMtx();

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// X�t�@�C���̃f�[�^�擾
	CXLoad::SXFile *pXData = CScene::GetXLoad()->GetMyObject(m_nIdxXFile);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pXData->pBuffMat->GetBufferPointer();

	// ���_�����J��Ԃ�
	for (int nCntMat = 0; nCntMat < (int)pXData->dwNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, CManager::GetInstance()->GetTexture()->GetAdress(m_nIdxTexture[nCntMat]));

		// �p�[�c�̕`��
		pXData->pMesh->DrawSubset(nCntMat);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//==========================================================================
// �`�揈��
//==========================================================================
void CModel::Draw(D3DXCOLOR col)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL matNow;			// ����̃}�e���A��

	// ���̏��N���A
	ZeroMemory(&matNow, sizeof(D3DXMATERIAL));
	matNow.MatD3D.Diffuse = col;
	matNow.MatD3D.Ambient = col;

	// ���[���h�}�g���b�N�X�̌v�Z����
	CalWorldMtx();

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// X�t�@�C���̃f�[�^�擾
	CXLoad::SXFile *pXData = CScene::GetXLoad()->GetMyObject(m_nIdxXFile);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pXData->pBuffMat->GetBufferPointer();

	// ���_�����J��Ԃ�
	for (int nCntMat = 0; nCntMat < (int)pXData->dwNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&matNow.MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, CManager::GetInstance()->GetTexture()->GetAdress(m_nIdxTexture[nCntMat]));

		// �p�[�c�̕`��
		pXData->pMesh->DrawSubset(nCntMat);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//==========================================================================
// �`�揈��
//==========================================================================
void CModel::Draw(float fAlpha)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X�錾
	D3DXMATRIX mtxRotOrigin;		// �v�Z�p�}�g���b�N�X�錾
	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxnParent;			// �e�̌v�Z�p�}�g���b�N�X

	D3DXMATERIAL matNow;			// ����̃}�e���A��

	// ���̏��N���A
	ZeroMemory(&matNow, sizeof(D3DXMATERIAL));

	// ���[���h�}�g���b�N�X�̌v�Z����
	CalWorldMtx();

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// X�t�@�C���̃f�[�^�擾
	CXLoad::SXFile *pXData = CScene::GetXLoad()->GetMyObject(m_nIdxXFile);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pXData->pBuffMat->GetBufferPointer();

	// ���_�����J��Ԃ�
	for (int nCntMat = 0; nCntMat < (int)pXData->dwNumMat; nCntMat++)
	{
		// �s�����x�ݒ�
		matNow.MatD3D.Diffuse = D3DXCOLOR(pMat[nCntMat].MatD3D.Diffuse.r, pMat[nCntMat].MatD3D.Diffuse.g, pMat[nCntMat].MatD3D.Diffuse.b, fAlpha);
		matNow.MatD3D.Ambient = D3DXCOLOR(pMat[nCntMat].MatD3D.Ambient.r, pMat[nCntMat].MatD3D.Ambient.g, pMat[nCntMat].MatD3D.Ambient.b, fAlpha);
		matNow.MatD3D.Emissive = pMat[nCntMat].MatD3D.Emissive;
		matNow.MatD3D.Power = pMat[nCntMat].MatD3D.Power;
		matNow.MatD3D.Specular = pMat[nCntMat].MatD3D.Specular;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&matNow.MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, CManager::GetInstance()->GetTexture()->GetAdress(m_nIdxTexture[nCntMat]));

		// �p�[�c�̕`��
		pXData->pMesh->DrawSubset(nCntMat);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//==========================================================================
// �e�N�X�`���̃C���f�b�N�X���蓖��
//==========================================================================
void CModel::SetIdxTexture(int i, int nIdx)
{
	m_nIdxTexture[i] = nIdx;
}

//==========================================================================
// �e�N�X�`���C���f�b�N�X�ԍ����蓖��
//==========================================================================
int CModel::GetIdxTexture(int nIdx)
{
	return m_nIdxTexture[nIdx];
}

//==========================================================================
// �}�g���b�N�X�ݒ�
//==========================================================================
void CModel::SetWorldMtx(const D3DXMATRIX mtx)
{
	m_mtxWorld = mtx;
}

//==========================================================================
// �}�g���b�N�X�擾
//==========================================================================
D3DXMATRIX CModel::GetWorldMtx(void) 
{
	return m_mtxWorld;
}

//==========================================================================
// �|�C���^�}�g���b�N�X�擾
//==========================================================================
D3DXMATRIX *CModel::GetPtrWorldMtx(void)
{
	return &m_mtxWorld;
}

//==========================================================================
// �ʒu�ݒ�
//==========================================================================
void CModel::SetPosition(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==========================================================================
// �ʒu�擾
//==========================================================================
D3DXVECTOR3 CModel::GetPosition(void) const
{
	return m_pos;
}

//==========================================================================
// �ʒu�ݒ�
//==========================================================================
void CModel::SetOldPosition(const D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}

//==========================================================================
// �ʒu�擾
//==========================================================================
D3DXVECTOR3 CModel::GetOldPosition(void) const
{
	return m_posOld;
}

//==========================================================================
// ���̈ʒu�ݒ�
//==========================================================================
void  CModel::SetOriginPosition(const D3DXVECTOR3 pos)
{
	m_posOrigin = pos;
}

//==========================================================================
// ���̈ʒu�擾
//==========================================================================
D3DXVECTOR3  CModel::GetOriginPosition(void) const
{
	return m_posOrigin;
}

//==========================================================================
// �����ݒ�
//==========================================================================
void CModel::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//==========================================================================
// �����擾
//==========================================================================
D3DXVECTOR3 CModel::GetRotation(void) const
{
	return m_rot;
}

//==========================================================================
// ���̌����ݒ�
//==========================================================================
void CModel::SetOriginRotation(const D3DXVECTOR3 rot)
{
	m_rotOrigin = rot;
}

//==========================================================================
// ���̌����擾
//==========================================================================
D3DXVECTOR3 CModel::GetOriginRotation(void) const
{
	return m_rotOrigin;
}

//==========================================================================
// �X�P�[���ݒ�
//==========================================================================
void CModel::SetScale(const D3DXVECTOR3 scale)
{
	m_scale = scale;
}

//==========================================================================
// �X�P�[���擾
//==========================================================================
D3DXVECTOR3 CModel::GetScale(void) const
{
	return m_scale;
}

//==========================================================================
// ���_�̍ő�l�擾
//==========================================================================
D3DXVECTOR3 CModel::GetVtxMax(void) const
{
	// X�t�@�C���̃f�[�^�擾
	return CScene::GetXLoad()->GetMyObject(m_nIdxXFile)->vtxMax;
}

//==========================================================================
// ���_�̍ŏ��l�擾
//==========================================================================
D3DXVECTOR3 CModel::GetVtxMin(void) const
{
	// X�t�@�C���̃f�[�^�擾
	return CScene::GetXLoad()->GetMyObject(m_nIdxXFile)->vtxMin;
}

//==========================================================================
// ���f���I�u�W�F�N�g�̎擾
//==========================================================================
CModel *CModel::GetModel(void)
{
	return this;
}

//==========================================================================
// �����擾
//==========================================================================
int CModel::GetNumAll(void)
{
	return m_nNumAll;
}
