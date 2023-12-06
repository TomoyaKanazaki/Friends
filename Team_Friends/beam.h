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

	CBeam(int nPriority = mylib_const::PRIORITY_DEFAULT);
	~CBeam();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	static CBeam *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXCOLOR col, const float fRadius, const float fLength, const int nLife, const int nDisity, const int nDamage, CCollisionObject::eMyTag TagType);

private:

	// �����o�ϐ�
	float m_fRadius;	// ���a
	float m_fLength;	// ����
	int m_nDisity;		// ���x
	int m_nDamage;		// �_���[�W
	D3DXCOLOR m_color;	// �F
	std::vector<CEffect3D*> m_pEffect;	// �G�t�F�N�g�̃I�u�W�F�N�g
	CCollisionObject::eMyTag m_Tag;	// �^�O
	int m_nLife;	// ����
};


#endif