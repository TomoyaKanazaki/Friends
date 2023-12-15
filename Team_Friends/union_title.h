//=============================================================================
// 
//  �^�C�g�����̃v���C���[�w�b�_�[ [union_title.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _UNION_TITLE_H_
#define _UNION_TITLE_H_

#include "player_union.h"

//==========================================================================
// �N���X��`
//==========================================================================
// �^�C�g�����̃N���X��`
class CUnionTitle : public CPlayerUnion
{
public:

	CUnionTitle(int nPriority = mylib_const::PRIORITY_DEF2D);
	~CUnionTitle();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void) override;
	void Update(void) override;

	// �ÓI�����o�֐�
	static CUnionTitle* Create(D3DXVECTOR3 pos);

	// ���̑��֐�
	void SetEnablePressEnter(void) { m_bPressEnter = true; }	// �G���^�[��������L��
	bool IsPressEnter(void) { return m_bPressEnter; }			// �G���^�[��������擾

private:

	// �񋓌^��`
	enum MOTION
	{
		MOTION_DEF = 0,	// �j���[�g�������[�V����
		MOTION_STARTUP,	// �N�����[�V����
		MOTION_MAX
	};

	// �����o�֐�
	void AttackAction(int nIdx, int nModelNum, CMotion::AttackInfo ATKInfo, int nCntATK) override;	// �U��������
	void AttackInDicision(int nIdx, CMotion::AttackInfo ATKInfo) override;				// �U�����蒆����
	HRESULT CreateParts(void) override;													// �p�[�c�̐ݒ�

	// �����o�ϐ�
	bool m_bPressEnter;	// �G���^�[�̉�������
};

#endif
