//=============================================================================
// 
//  �G���A�����}�l�[�W���w�b�_�[ [limitereamanager.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _LIMITEREAMANAGER_H_
#define _LIMITEREAMANAGER_H_	// ��d�C���N���[�h�h�~

#include "constans.h"
#include "limitarea.h"

//==========================================================================
// �N���X��`
//==========================================================================
// �G���A�����̃}�l�[�W���N���X��`
class CLimitAreaManager
{
public:

	CLimitAreaManager();
	~CLimitAreaManager();

	HRESULT Init(void);
	void Uninit(void);

	static CLimitAreaManager *Create(void);

	int Regist(CLimitArea *pBullet);	// ���蓖��
	void Delete(int nIdx);			// �폜
	int GetNumAll(void);			// �G���A�����̑����擾
	CLimitArea **GetLimitErea(void);		// �G���A�����̃I�u�W�F�N�g�擾
protected:


private:

	CLimitArea *m_apLimitErea[mylib_const::MAX_LIMITEREA];	// �G���A�����̃I�u�W�F�N�g
	int m_nNumAll;		// �G���A�����̑���

};



#endif