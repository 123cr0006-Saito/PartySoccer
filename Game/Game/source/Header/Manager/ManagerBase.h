//----------------------------------------------------------------------
// @filename ManagerBase.h
// @author: saito ko
// @explanation
// Managerの基底クラス
//----------------------------------------------------------------------
#pragma once
#include "dxlib.h"
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
#include <tuple>
class ManagerBase
{
	public:
	virtual ~ManagerBase() = default;
	virtual bool Terminate() = 0;
	virtual bool UpdateInit();
	virtual bool Update();
	virtual bool UpdateEnd();
	virtual bool Draw();

	// データの追加
	template<typename T>
	void Add(T* value) {
		void* ptr = static_cast<void*>(value);
		AddInput(ptr);
	};
	// データの削除
	template<typename U>
	void Delete(U* value) {
		void* ptr = static_cast<void*>(value);
		DeleteInput(ptr);
	};

	virtual void AddInput(void* value){};

	virtual void DeleteName(const std::string& deleteName){};
	virtual void DeleteInput(void* value){};
	virtual void DelAll(){};

	std::string GetName() const { return _name; }

protected:
	std::string _name; // 名前
};

