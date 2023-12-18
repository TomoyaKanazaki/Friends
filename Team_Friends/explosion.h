//=============================================================================
// 
//  �����w�b�_�[ [explosion.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_	// ��d�C���N���[�h�h�~

#include "meshsphere.h"

//==========================================================================
// �N���X��`
//==========================================================================
// �����N���X��`
class CExplosion : public CMeshSphere
{
public:

	// �񋓌^��`
	enum TYPE
	{
		TYPE_PLAYER = 0,	// �v���C���[�̔���
		TYPE_ENEMY,			// �G�̔���
		TYPE_MAX
	};

	enum STATE
	{
		STATE_NONE = 0,	// �Ȃɂ��Ȃ�
		STATE_DMG,		// �_���[�W
		STATE_FADEOUT,	// �t�F�[�h�A�E�g
		STATE_MAX
	};

	CExplosion(int nPriority = 6);
	~CExplosion();


	// �I�[�o�[���C�h���ꂽ�֐�
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void SetVtx(void);

	TYPE GetType(void);			// ��ގ擾
	void SetState(STATE state, int nCntState);	// ��Ԑݒ�
	STATE GetState(void);	// ��Ԏ擾

	static CExplosion *Create(TYPE type, const D3DXVECTOR3 pos, const float fSize);

private:

	// �����o�֐�
	void UpdatePos(void);		// �ړ�
	void CollisionPlayer(void);		// �v���C���[�Ƃ̔���
	void CollisionEnemy(void);		// �G�Ƃ̔���
	
	// ��ԍX�V
	void StateNone(void);		// �����Ȃ����
	void StateDamage(void);		// �_���[�W��ԏ���
	void StateFadeout(void);	// �t�F�[�h�A�E�g��ԏ���

	// �����o�ϐ�
	TYPE m_type;		// �����̎��
	STATE m_state;		// ���
	int m_nCntState;	// ��ԑJ�ڃJ�E���^�[
	int m_nLife;		// ����
	int m_nLifeMax;		// �����̍ő�l
	int m_nTexIdx;		// �e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nCntEmission;	// �������̃J�E���^�[
	float m_fDestSize;	// �ڕW�̃T�C�Y

	typedef void(CExplosion::*STATE_FUNC)(void);
	typedef void(CExplosion::*COLLISION_FUNC)(void);
	static STATE_FUNC m_FuncList[];
	static COLLISION_FUNC m_CollisionFuncList[];	// �����蔻��̃��X�g
};


#endif