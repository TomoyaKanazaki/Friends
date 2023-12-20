//==========================================
//
//  �������b�Z�[�W(message_win.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MESSAGE_WIN_H_
#define _MESSAGE_WIN_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CMessageWin : public CObject3D
{
public:

	//�����o�֐�
	CMessageWin();
	~CMessageWin();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// �ÓI�����o�֐�
	static CMessageWin* Create();

private:

	// �����o�֐�
	void Move(); //�ړ�

	// �����o�ϐ�
	float m_fSec; // �o�ߎ���
	bool m_bMove; // �ړ������t���O
	int m_nIdx; // ���g�̃C���f�b�N�X
	D3DXVECTOR3 pos_target; // �ڕW�ʒu

	// �ÓI�����o�ϐ�
	static int nIdx;

};

#endif
