//=============================================================================
// 
//  �v���C���[�w�b�_�[ [player_title.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _PLAYER_TITLE_H_
#define _PLAYER_TITLE_H_	// ��d�C���N���[�h�h�~

#include "player.h"

//==========================================================================
// �N���X��`
//==========================================================================
class CPlayerTitle : public CPlayer
{
public:

	//�^�C�v
	enum MODEL
	{
		PLAYER_UNION = 0, //���̂�[��
		PLAYER_ARM, //�r�̂��
		PLAYER_LEG, //���̂��
		PLAYER_BODY, //���̂��
		MAX,
		NONE
	};

	CPlayerTitle(int nPriority = mylib_const::PRIORITY_DEF2D);
	~CPlayerTitle();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void SetTarget(const float pos) { m_posTarget = pos; };
	void IsMove(bool bMove) { m_bMove = bMove; } // �ړ��t���O

	// �ÓI�����o�֐�
	static CPlayerTitle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL type = PLAYER_UNION);

private:

	// �����o�֐�
	void Rotation(void); // ��]
	void Move(void); // �ړ�
	void Fly(void); // ��яオ��
	void Forward(void); // ����o��

	//�����o�ϐ�
	int m_nModelType;
	float m_posTarget; // �ړI�n
	bool m_bMove; // �ړ��t���O

	// �ÓI�����o�ϐ�
	static int m_nIdx; // �C���f�b�N�X

};

#endif
