//=============================================================================
// 
//  �G���A�����w�b�_�[ [limitarea.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _LIMITAREA_H_
#define _LIMITAREA_H_	// ��d�C���N���[�h�h�~

#include "meshwall.h"

//==========================================================================
// �N���X��`
//==========================================================================
// �G���A�����N���X��`
class CLimitErea : public CObject
{
public:

	// �G���A�\����
	struct sLimitEreaInfo
	{
		float fMinX;	// �ŏ�X
		float fMaxX;	// �ő�X
		float fMinZ;	// �ŏ�Z
		float fMaxZ;	// �ő�Z
	};

	CLimitErea(int nPriority = 7);
	~CLimitErea();

	// �I�[�o�[���C�h���ꂽ�֐�
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void Release(void);

	static CLimitErea *Create(sLimitEreaInfo info);
	sLimitEreaInfo GetLimitEreaInfo(void);
protected:

private:

	void UpdateColor(int nIdx);

	CMeshWall *m_pMeshWall[mylib_const::SHAPE_LIMITEREA];	// ���b�V���E�H�[���̃I�u�W�F�N�g
	sLimitEreaInfo m_sLimitEreaInfo;	// �G���A�������
	int m_nIdxEreaManager;				// �G���A�����}�l�[�W���̃C���f�b�N�X�ԍ�
};



#endif