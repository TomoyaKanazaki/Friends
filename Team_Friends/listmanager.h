//==========================================================================
//
// ���X�g�}�l�[�W���w�b�_�[[listmanager.h]
// Author�F���n�Ή�
//
//==========================================================================
#ifndef _LISTMANAGER_H_
#define _LISTMANAGER_H_	// ��d�C���N���[�h�h�~

//==========================================================================
// ���X�g�}�l�[�W���N���X�̒�`
//==========================================================================
template<class T> class CListManager
{
public:

	CListManager();			// �R���X�g���N�^
	~CListManager();		// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);

	void Regist(T *pItem);			// ���蓖��
	void Delete(T *pItem);			// �폜
	void KillAll(void);				// �S�č폜
	int GetNumAll(void);			// �A�C�e���̑����擾
	std::list<T*> GetList(void);	// �A�C�e���̃��X�g�擾

private:

	int m_nNumAll;				// ����
	std::list<T*> m_ListObj;	// ���X�g
};



//==========================================================================
// �R���X�g���N�^
//==========================================================================
template<class T> CListManager<T>::CListManager()
{
	// �l�̃N���A
	m_nNumAll = 0;	// �������Z�b�g
	m_ListObj.clear();	// �A�C�e���̃��X�g
}

//==========================================================================
// �f�X�g���N�^
//==========================================================================
template<class T> CListManager<T>::~CListManager()
{

}

//==========================================================================
// ����������
//==========================================================================
template<class T> HRESULT CListManager<T>::Init(void)
{
	// �������Z�b�g
	m_nNumAll = 0;

	return S_OK;
}

//==========================================================================
// ���蓖��
//==========================================================================
template<class T> void CListManager<T>::Regist(T *pItem)
{
	// �A�C�e���̃��X�g�ɒǉ�
	m_ListObj.push_back(pItem);

	// �������Z
	m_nNumAll++;
}

//==========================================================================
// �폜
//==========================================================================
template<class T> void CListManager<T>::Delete(T *pItem)
{
	// �������g�����X�g����T��
	std::list<T*>::iterator itr = std::find(m_ListObj.begin(), m_ListObj.end(), pItem);
	m_ListObj.erase(itr);

	// �������Z
	m_nNumAll--;
}

//==========================================================================
// �I������
//==========================================================================
template<class T> void CListManager<T>::Uninit(void)
{
	// �N���A
	m_ListObj.clear();

	// ����
	m_nNumAll = 0;
}

//==========================================================================
// �S�č폜
//==========================================================================
template<class T> void CListManager<T>::KillAll(void)
{
	std::list<T*>::iterator it = m_ListObj.begin();

	// �v�f���J��Ԃ�
	while (it != m_ListObj.end())
	{
		// �I������
		(*it)->Uninit();

		// �擪�̗v�f��n��
		it = m_ListObj.begin();
		m_nNumAll--;
	}

	// �N���A
	m_ListObj.clear();

	// ����
	m_nNumAll = 0;

}

//==========================================================================
// �����擾
//==========================================================================
template<class T> int CListManager<T>::GetNumAll(void)
{
	return m_nNumAll;
}

//==========================================================================
// ���X�g�擾
//==========================================================================
template<class T> std::list<T*> CListManager<T>::GetList(void)
{
	return m_ListObj;
}


#endif