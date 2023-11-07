//=============================================================================
// 
//  �A�C�e���w�b�_�[ [item.h]
//  Author : ���c����
// 
//=============================================================================

#ifndef _ITEM_H_
#define _ITEM_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "objectX.h"

class CThunderRing;
class CObjectBillboard;

//==========================================================================
// �N���X��`
//==========================================================================
// �A�C�e���N���X��`
class CItem : public CObjectX
{
public:

	// �񋓌^��`
	enum TYPE
	{
		TYPE_POWER = 0,	// �Η�
		TYPE_SPEED,		// �쓮��
		TYPE_LIFE,		// �ϋv��
		TYPE_MAX
	};

	enum STATE
	{
		STATE_NONE = 0,	// �Ȃɂ��Ȃ�
		STATE_DMG,		// ���˕Ԃ�
		STATE_FADEOUT,	// �t�F�[�h�A�E�g���
		STATE_MAX		// �����F�t�F�[�h�ƃX�|�[�������K�v
	};

	CItem(int nPriority = 6);
	~CItem();


	// �I�[�o�[���C�h���ꂽ�֐�
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void SetType(TYPE type);	// ��ސݒ�
	TYPE GetType(void);	// ��ގ擾
	void SetState(STATE state, int nCntState);	// ��Ԑݒ�
	STATE GetState(void);	// ��Ԏ擾

	static int GetNumAll(void);
	static CItem *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

private:
	void UpdatePos(void);		// �ړ�
	void UpdateTypePlayer(void);	// �v���C���[�e�̍X�V
	void CollisionPlayer(void);		// �v���C���[�Ƃ̔���
	
	void StateNone(void);		// �����Ȃ����
	void StateDamage(void);		// �_���[�W��ԏ���
	void StateFadeOut(void);		// �t�F�[�h�A�E�g����


	TYPE m_type;				// ���
	STATE m_state;				// ���
	int m_nCntState;			// ��ԑJ�ڃJ�E���^�[
	int m_nIdxBulletManager;			// �e�}�l�[�W���̃C���f�b�N�X�ԍ�
	int m_nLife;							// ����
	int m_nLifeMax;					// �����̍ő�l
	static int m_nNumAll;					// �e�̑���
	static const char *m_apModelFile[TYPE_MAX];	// ���f���̃t�@�C��
	int m_nModelIdx;				// ���f���̃C���f�b�N�X�ԍ�
	int m_nCntEmission;	// �������̃J�E���^�[

	typedef void(CItem::*STATE_FUNC)(void);
	static STATE_FUNC m_StateFuncList[];
};


#endif