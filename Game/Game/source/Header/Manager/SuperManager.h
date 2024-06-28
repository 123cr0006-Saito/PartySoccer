//----------------------------------------------------------------------
// @filename SuperManager.h
// @author: saito ko
// @explanation
// マネージャークラスを管理するクラス
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
	static SuperManager* _instance; // インスタンス
	bool _isSort;// ソートをするかどうかのフラグ
	std::vector<std::tuple<std::string,int,class ManagerBase*>> _superManager;// マネージャークラスのリスト
	std::vector<std::string> _delSuperManager;// 削除するマネージャークラスのリスト
	bool _isProcessSkip;// 処理を飛ばすかどうかのフラグ
};

