//=============================================================================
// 
//  �K�E�E�B���h�E�w�b�_�[ [ultwindow.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _ULTWINDOW_H_
#define _ULTWINDOW_H_	// ��d�C���N���[�h�h�~

#include "object.h"
#include "gamemanager.h"

//==========================================================================
// �O���錾
//==========================================================================
class CObjectCircleGauge2D;
class CMultiNumber;

//==========================================================================
// �N���X��`
//==========================================================================
// �K�E�E�B���h�E�N���X��`
class CUltWindow : public CObject
{
public:

	CUltWindow(int nPriority = 7);
	~CUltWindow();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetEnableCharge(bool bEnd) { m_bEndCharge = bEnd; }	// �`���[�W�̃t���O
	bool IsEndCharge() { return m_bEndCharge; }	// �`���[�W���I����Ă邩
	CObjectCircleGauge2D *GetGauge();	// �Q�[�W�擾
	static CUltWindow *Create(D3DXVECTOR3 pos, bool bJoin);
private:
	
	// �����o�֐�
	void GaugeFlash(void);	// �Q�[�W�̓_�ŏ���

	// �����o�ϐ�
	bool m_bJoin;	// �Q�����Ă邩
	CObject2D *m_pOnOffSign[2];			// �I���I�t�T�C��
	CObject2D *m_pUltText;					// �K�E�e�L�X�g
	CObject2D *m_pWindowShape;				// �E�B���h�E�̌^
	CObject2D *m_pWindowShapeLid;			// �E�B���h�E�̌^�̊W
	CObjectCircleGauge2D *m_pCircleGauge2D;	// �~�Q�[�W�̃|�C���^
	CMultiNumber *m_pUltNumber;				// �K�E�̐���
	float m_fColorFlashValue;				// �_�ł̐F
	bool m_bEndCharge;						// �`���[�W����
};



#endif