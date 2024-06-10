#include "../../Header/Manager/CollisionManager.h"
#include "../../AppFrame/source/Application/UtilMacro.h"
#include "../../AppFrame/source/System/Header/Collision/3DCollision.h"
CollisionManager* CollisionManager::_instance = nullptr;
CollisionManager::CollisionManager(){
	_instance = this;
};

CollisionManager::~CollisionManager(){

};

void CollisionManager::Add(ObjectBase* object, CollisionBase* collision){
	_collisionList.push_back(std::make_pair(object,collision));
};

bool CollisionManager::Update(){
	for(auto&& first :_collisionList){
		if(first.second->name == "player"){
			CollisionCheckForPlayer(first);
		}
		else if(first.second->name == "ball"){
			CollisionCheckForBall(first);
		}
		else{
			DebugErrar();
			return false;
		}
	}
	return true;
};

bool CollisionManager::CollisionCheckForPlayer(std::pair<ObjectBase*, CollisionBase*> first){

	Capsule* capsule = dynamic_cast<Capsule*>(first.second);

	// キャスト失敗
	if(!capsule){
		DebugErrar();
		return false;
	}

	for (auto&& second : _collisionList) {
		if(second.second->name == "player"){
			Capsule* capsule2 = dynamic_cast<Capsule*>(second.second);
			// キャスト失敗
			if (!capsule2) {
				DebugErrar();
				return false;
			}

			if (Collision3D::TwoCapsuleCol((*capsule), (*capsule2))) {
				//衝突処理
			}
		}
		else if (second.second->name == "ball") {
			Sphere* sphere = dynamic_cast<Sphere*>(second.second);
			// キャスト失敗
			if (!sphere) {
				DebugErrar();
				return false;
			}
			if (Collision3D::SphereCapsuleCol((*sphere),(*capsule))) {
				//衝突処理
			}
		}
		else {
			DebugErrar();
			return false;
		}
	}
	return true;
};

bool CollisionManager::CollisionCheckForBall(std::pair<ObjectBase*, CollisionBase*> first){
	for (auto&& second : _collisionList) {
		if (second.second->name == "player") {

		}
		else if (second.second->name == "ball") {

		}
		else {
			DebugErrar();
			return false;
		}
	}
	return true;
};
