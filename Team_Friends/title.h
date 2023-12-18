//=============================================================================
// 
//  �^�C�g���w�b�_�[ [title.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _TITLE_H_
#define _TITLE_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "manager.h"

//==========================================
//  �O���錾
//==========================================
class CTitleLogo;
class CUnionTitle;
class CPlayerTitle;

//==========================================================================
// �N���X��`
//==========================================================================
// �^�C�g���N���X��`
class CTitle : public CScene
{
public:

	CTitle();
	~CTitle();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetEnablePressEnter(void) { m_bPressEnter = true; }	// �G���^�[��������L��
	static bool IsPressEnter(void) { return m_bPressEnter; }			// �G���^�[��������擾

private:

	// �����o�֐�
	void WhiteOut();

	// �����o�ϐ�
	D3DXCOLOR m_col;
	float m_fLength;

	float m_fCnt;		// �؂�ւ��̃J�E���^�[
	int m_nCntEmission;	// �������J�E���^�[
	CTitleLogo *m_pLogo;
	CUnionTitle *m_pUnionTitle;	// �^�C�g���̍��̃v���C���[�I�u�W�F�N�g
	static bool m_bPressEnter;			// �G���^�[��������
	CPlayerTitle* m_apPlayer[4]; // �v���C���[�̃|�C���^�z��

};



#endif