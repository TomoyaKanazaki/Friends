//=============================================================================
// 
//  �K�E�̃J�b�g�C���w�b�_�[ [ultcutin.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _ULTCUNTIN_H_
#define _ULTCUNTIN_H_	// ��d�C���N���[�h�h�~

#include "object2D_Anim.h"

//==========================================================================
// �N���X��`
//==========================================================================
// �K�E�̃J�b�g�C���N���X��`
class CUltCutin : public CObject2D_Anim
{
public:

	CUltCutin(int nPriority = 8);
	~CUltCutin();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void) override;
	void Update(void) override;
	void Draw(void) override;

	static CUltCutin *Create(void);	// ��������
	static void LoadTexture(void);	// �e�N�X�`���ǂݍ���
private:

	// �����o�ϐ�
	static int m_nTexIdx;	// �e�N�X�`���̃C���f�b�N�X�ԍ�
};



#endif