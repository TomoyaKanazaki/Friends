//==========================================
// 
//  �l���I�����(decide.h)
//  Author : Tomoya Kanazaki
// 
//==========================================
#ifndef _DECIDE_H_
#define _DECIDE_H_
#include "scene.h"

//==========================================
// �N���X��`
//==========================================
class CDecide : public CScene
{
public:

	CDecide();
	~CDecide();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

};

#endif
