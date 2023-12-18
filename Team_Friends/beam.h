//=============================================================================
// 
//  �r�[���w�b�_�[ [beam.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _BEAM_H_
#define _BEAM_H_	// ��d�C���N���[�h�h�~

#include "object.h"
#include "collisionobject.h"

//==========================================================================
// �O���錾
//==========================================================================
class CEffect3D;

namespace my_beam
{
	const int DEFAULTDENSITY_BEAM = 12;	// �r�[���̖��x
}

//==========================================================================
// �N���X��`
//==========================================================================
// �r�[���N���X��`
class CBeam : public CObject
{
public:

	// �r�[���̎�ޗ�
	enum eBeamType
	{
		TYPE_NORMAL = 0,	// �ʏ�
		TYPE_RESIDUAL,		// �c��
		TYPE_MAX
	};

	CBeam(int nPriority = mylib_const::PRIORITY_ZSORT);
	~CBeam();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	static CBeam *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXCOLOR col, const float fRadius, const float fLength, const int nLife, const int nDisity, const int nDamage, CCollisionObject::eMyTag TagType, eBeamType BeamType = TYPE_NORMAL);
	void SetDisableAddAlpha(void);	// ���Z����������

private:

	// �����o�֐�
	void UpdateEffect(void);
	void UpdateBillboard(void);

	// �����o�ϐ�
	float m_fRadius;		// ���a
	float m_fLength;		// ����
	float m_fDestLength;	// �ڕW�̒���
	float m_moveRatio;		// �ړ��̊���
	int m_nDisity;			// ���x
	int m_nDamage;			// �_���[�W
	D3DXCOLOR m_color;		// �F
	std::vector<CEffect3D*> m_pEffect;	// �G�t�F�N�g�̃I�u�W�F�N�g
	std::vector<CObjectBillboard*> m_pObjBillboard;	// �r���{�[�h�̃I�u�W�F�N�g
	CCollisionObject::eMyTag m_Tag;	// �^�O
	eBeamType m_BeamType;	// �r�[���̎��
	int m_nLife;	// ����
	int m_nLifeOrigin;	// ����
	int m_nCntEmission;		// �������̃J�E���^�[
	static int m_nTexIdx;	// �e�N�X�`���̃C���f�b�N�X�ԍ�
};


#endif