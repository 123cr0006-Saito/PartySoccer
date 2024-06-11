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
			// shoot��gool�̔����ball�Ƃ̂ݍs������ball�̂ق��ŏ���������
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

	// �L���X�g���s
	if(!capsule){
		DebugErrar();
		return false;
	}

	for (auto&& second : _collisionList) {

		if (first == second)continue;
		if (second.second->name == "shoot" || second.second->name == "gool")continue;

		if(second.second->name == "player"){
			Capsule* capsule2 = dynamic_cast<Capsule*>(second.second);
			// �L���X�g���s
			if (!capsule2) {
				DebugErrar();
				return false;
			}

			if (Collision3D::TwoCapsuleCol((*capsule), (*capsule2))) {
				//�Փˏ���
				int power = first.first->GetPower() - second.first->GetPower();
				if (power > 0) {
					// player2�𐁂���΂�
				}
				else if(power < 0){
					// player1�𐁂���΂�
				}
				else {
					//�����o������
				}
			}
		}
		else if (second.second->name == "ball") {
			Sphere* sphere = dynamic_cast<Sphere*>(second.second);
			// �L���X�g���s
			if (!sphere) {
				DebugErrar();
				return false;
			}
			if (Collision3D::SphereCapsuleCol((*sphere),(*capsule))) {
				//�Փˏ���
				bool IsShoot = dynamic_cast<Ball*>(second.first)->GetIsShoot();

				if (IsShoot) {
					// player1�𐁂���΂�
				}
				else {
					// �����΂�
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

	// �L���X�g���s
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