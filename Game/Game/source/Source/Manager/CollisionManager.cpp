#include "../../Header/Manager/CollisionManager.h"
#include "../../AppFrame/source/Application/UtilMacro.h"
#include "../../AppFrame/source/System/Header/Collision/3DCollision.h"
#include "../../Header/Object/Stage/Ball.h"
#include "../../Header/Object/Player/Player.h"
CollisionManager* CollisionManager::_instance = nullptr;
CollisionManager::CollisionManager(){
	_instance = this;
};

CollisionManager::~CollisionManager(){

};

void CollisionManager::Add(ObjectBase* object, CollisionBase* collision){
	_addCollisionList.push_back(std::make_pair(object,collision));
};

void  CollisionManager::Del(std::string name){
	_delCollisionList.push_back(name);
};

std::string CollisionManager::GetListName(std::string name) {
	for (auto list : _collisionList) {
		std::string str = list.second->name;
		if (str == name) {
			return str;
		}
	}
	return "";
};

int CollisionManager::GetListSize() {
	return _collisionList.size();
};

bool CollisionManager::Update(){

	// deleteListの中に値があるとき削除
	for (auto list : _delCollisionList) {
		for (auto itr = _collisionList.begin(); itr != _collisionList.end(); itr++) {
			if (itr->second->GetName() == list) {
				delete itr->second;
				itr = _collisionList.erase(itr);
				break;
			}
		}
	}

	// addListの中に値があるとき追加
	for (auto list : _addCollisionList) {
		_collisionList.push_back(list);
	}

	// addListとdeleteListをクリア
	_addCollisionList.clear();
	_delCollisionList.clear();

	// 衝突判定
	for(auto&& first :_collisionList){

		if (first.second->name == "shoot" || first.second->name == "goal") {
			// shootとgoalの判定はballとのみ行うためballのほうで処理をする
			continue;
		}

		if(first.second->name == "player"){
			CollisionCheckForCapsule(first);
		}
		else if(first.second->name == "ball"){
			CollisionCheckForSphere(first);
		}
	}
	return true;
};

bool CollisionManager::CollisionCheckForCapsule(std::pair<ObjectBase*, CollisionBase*>& first){

	Capsule* capsule = dynamic_cast<Capsule*>(first.second);

	// キャスト失敗
	if(!capsule){
		DebugErrar();
		return false;
	}

	for (auto&& second : _collisionList) {

		if (first == second)continue;
		if (second.second->name == "shoot" || second.second->name == "goal")continue;

		if(second.second->name == "player"){
			Capsule* capsule2 = dynamic_cast<Capsule*>(second.second);
			// キャスト失敗
			if (!capsule2) {
				DebugErrar();
				return false;
			}

			if (Collision3D::TwoCapsuleCol((*capsule), (*capsule2))) {
				//衝突処理
				int speed = dynamic_cast<Player*>(first.first)->GetDash() - dynamic_cast<Player*>(second.first)->GetDash();
				if (speed > 0) {
					// player2を吹き飛ばす
				}
				else if(speed < 0){
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
				Vector3D pos1 = capsule->pos;
				Vector3D pos2 = sphere->pos;
				Ball* ball = dynamic_cast<Ball*>(second.first);
				if (IsShoot) {
					// player1を吹き飛ばす
					Vector3D dirVec = pos1 - pos2;
					dynamic_cast<Player*>(first.first)->SetKnockBack(350, dirVec);	
				}
				else {
					// 球を飛ばす
					Vector3D dirVec = pos2 - pos1;
					ball->SetForwardVec(dirVec);
					ball->SetSpeed(130);
				}
			}
		}
	}
	return true;
};

bool CollisionManager::CollisionCheckForSphere(std::pair<ObjectBase*, CollisionBase*>& first){

	Sphere* sphere1 = dynamic_cast<Sphere*>(first.second);

	// キャスト失敗
	if (!sphere1) {
		DebugErrar();
		return false;
	}

	for (auto&& second : _collisionList) {
		if (second.second->name == "player") {

		}
		else if (second.second->name == "shoot") {
			Sphere* sphere2 = dynamic_cast<Sphere*>(second.second);
			if (!sphere2) {
				DebugErrar();
				return false;
			}
			if (Collision3D::SphereCol((*sphere1), (*sphere2))) {
				Vector3D pos1 = sphere1->pos;
				Vector3D pos2 = sphere2->pos;
				Vector3D dirVec =  pos1 - pos2;
				Ball* ball = dynamic_cast<Ball*>(first.first);
				Player* player = static_cast<Player*>(second.first);
				if (!ball) {
					DebugErrar();
					return false;
				}
				ball->SetForwardVec(dirVec);
				int power = player->GetPower();
				ball->SetSpeed(10*power);
			}
		}
		else if (second.second->name == "goal") {
			
		}
	}
	return true;
};