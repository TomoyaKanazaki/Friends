//=============================================================================
// 
//  �{�X�̗̑̓Q�[�W�w�b�_�[ [hp_gauge_boss.h]
//  Author : ���n�Ή�
// 
//=============================================================================

#ifndef _HP_GAUGE_BOSS_H_
#define _HP_GAUGE_BOSS_H_	// ��d�C���N���[�h�h�~

#include "main.h"
#include "object2D.h"

//==========================================================================
// �N���X��`
//==========================================================================
// �{�X�̗̑̓Q�[�W�N���X��`
class CHP_GaugeBoss : public CObject
{
public:

	CHP_GaugeBoss(int nPriority = 7);
	~CHP_GaugeBoss();


	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVtx(int nCntGauge);

	void Kill(void);
	void SetLife(int nLife);

	static CHP_GaugeBoss *Create(D3DXVECTOR3 pos, int nMaxLife);
private:

	// �񋓌^��`
	typedef enum
	{
		VTXTYPE_BASE = 0,	// ���Q�[�W
		VTXTYPE_GAUGE,		// �s���N�Q�[�W
		VTXTYPE_FRAM,		// �g
		VTXTYPE_MAX
	}VTXTYPE;

	// �\���̒�`
	struct SHP_Gauge
	{
		CObject2D *pObj2D;	// �I�u�W�F�N�g2D�̃I�u�W�F�N�g
		float fMaxWidth;	// ���̍ő�l
		float fWidthDest;	// ���̍���
		float fMaxHeight;	// �����̍ő�l
	};

	// �����o�֐�
	void GaugeDecrement(int nCntGauge);		// ��������

	// �����o�ϐ�
	SHP_Gauge m_HPGauge[VTXTYPE_MAX];		// HP�Q�[�W�̏��
	int m_nLife;							// �̗�
	int m_nMaxLife;							// �ő�̗�
};


#endif