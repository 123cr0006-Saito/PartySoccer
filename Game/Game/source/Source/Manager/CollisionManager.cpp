#include "../../Header/Manager/CollisionManager.h"
#include "../../AppFrame/source/Application/UtilMacro.h"
#include "../../AppFrame/source/System/Header/Collision/3DCollision.h"
#include "../../Header/Object/Stage/Ball.h"
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

		if (first.second->name == "shoot" || first.second->name == "gool") {
			// shootとgoolの判定はballとのみ行うためballのほうで処理をする
			continue;
		}

		if(first.second->name == "player"){
			CollisionCheckForCapsule(first);
		}
		else if(first.second->name == "ball"){
			CollisionCheckForSphere(first);
		}
		else{
			DebugErrar();
			return false;
		}
	}
	return true;
};

bool CollisionManager::CollisionCheckForCapsule(std::pair<ObjectBase*, CollisionBase*> first){

	Capsule* capsule = dynamic_cast<Capsule*>(first.second);

	// キャスト失敗
	if(!capsule){
		DebugErrar();
		return false;
	}

	for (auto&& second : _collisionList) {

		if (first == second)continue;
		if (second.second->name == "shoot" || second.second->name == "gool")continue;

		if(second.second->name == "player"){
			Capsule* capsule2 = dynamic_cast<Capsule*>(second.second);
			// キャスト失敗
			if (!capsule2) {
				DebugErrar();
				return false;
			}

			if (Collision3D::TwoCapsuleCol((*capsule), (*capsule2))) {
				//衝突処理
				int power = first.first->GetPower() - second.first->GetPower();
				if (power > 0) {
					// player2を吹き飛ばす
				}
				else if(power < 0){
					// player1を吹き飛ばす
				}
				else {
					//押し出し処理
				}
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
				bool IsShoot = dynamic_cast<Ball*>(second.first)->GetIsShoot();

				if (IsShoot) {
					// player1を吹き飛ばす
				}
				else {
					// 球を飛ばす
				}
			}
		}
		else {
			DebugErrar();
			return false;
		}
	}
	return true;
};

bool CollisionManager::CollisionCheckForSphere(std::pair<ObjectBase*, CollisionBase*> first){

	Sphere* sphere = dynamic_cast<Sphere*>(first.second);

	// キャスト失敗
	if (!sphere) {
		DebugErrar();
		return false;
	}

	for (auto&& second : _collisionList) {
		if (second.second->name == "player") {

		}
		else if (second.second->name == "shoot") {

		}
		else if (second.second->name == "gool") {
			
		}
		else {
			DebugErrar();
			return false;
		}
	}
	return true;
};