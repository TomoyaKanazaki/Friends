//=============================================================================
// 
//  �N�����̖ڃG�t�F�N�g�w�b�_�[ [effect_startupeye.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _EFFECT_STARTUPEYE_H_
#define _EFFECT_STARTUPEYE_H_	// ��d�C���N���[�h�h�~

#include "objectBillboard_Anim.h"

//==========================================================================
// �N���X��`
//==========================================================================
// �N�����̖ڃG�t�F�N�g�N���X��`
class CEffectStartupEye : public CObjectBillboardAnim
{
public:

	CEffectStartupEye(int nPriority = 8);
	~CEffectStartupEye();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void) override;
	void Update(void) override;
	void Draw(void) override;

	static CEffectStartupEye *Create(const D3DXVECTOR3 pos);	// ��������
	static void LoadTexture(void);	// �e�N�X�`���ǂݍ���
private:

	// �����o�ϐ�
	static int m_nTexIdx;	// �e�N�X�`���̃C���f�b�N�X�ԍ�
};



#endif