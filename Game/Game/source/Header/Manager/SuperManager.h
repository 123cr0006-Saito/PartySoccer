//----------------------------------------------------------------------
// @filename SuperManager.h
// @author: saito ko
// @explanation
// �}�l�[�W���[�N���X���Ǘ�����N���X
//----------------------------------------------------------------------
#pragma once
#include <vector>
#include <string>
#include <tuple>
#include <utility>
class SuperManager 
{
public:
	SuperManager();
	~SuperManager();
	bool Add(const std::string& name, const int id,class ManagerBase* manager);
	bool DeleteName(const std::string& name);
	bool DelAll();
	class ManagerBase* GetManager(const std::string& name);
	bool Update();
	bool Draw();

	void Sort();
	static SuperManager* GetInstance() { return _instance;}
	void Skip() { _isProcessSkip = true; }
protected:
	static SuperManager* _instance; // �C���X�^���X
	bool _isSort;// �\�[�g�����邩�ǂ����̃t���O
	std::vector<std::tuple<std::string,int,class ManagerBase*>> _superManager;// �}�l�[�W���[�N���X�̃��X�g
	std::vector<std::string> _delSuperManager;// �폜����}�l�[�W���[�N���X�̃��X�g
	bool _isProcessSkip;// �������΂����ǂ����̃t���O
};

