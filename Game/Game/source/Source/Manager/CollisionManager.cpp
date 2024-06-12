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

	// deleteList�̒��ɒl������Ƃ��폜
	for (auto list : _delCollisionList) {
		for (auto itr = _collisionList.begin(); itr != _collisionList.end(); itr++) {
			if (itr->second->GetName() == list) {
				delete itr->second;
				itr = _collisionList.erase(itr);
				break;
			}
		}
	}

	// addList�̒��ɒl������Ƃ��ǉ�
	for (auto list : _addCollisionList) {
		_collisionList.push_back(list);
	}

	// addList��deleteList���N���A
	_addCollisionList.clear();
	_delCollisionList.clear();

	// �Փ˔���
	for(auto&& first :_collisionList){

		if (first.second->name == "shoot" || first.second->name == "goal") {
			// shoot��goal�̔����ball�Ƃ̂ݍs������ball�̂ق��ŏ���������
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

	// �L���X�g���s
	if(!capsule){
		DebugErrar();
		return false;
	}

	for (auto&& second : _collisionList) {

		if (first == second)continue;
		if (second.second->name == "shoot" || second.second->name == "goal")continue;

		if(second.second->name == "player"){
			Capsule* capsule2 = dynamic_cast<Capsule*>(second.second);
			// �L���X�g���s
			if (!capsule2) {
				DebugErrar();
				return false;
			}

			if (Collision3D::TwoCapsuleCol((*capsule), (*capsule2))) {
				//�Փˏ���
				int speed = dynamic_cast<Player*>(first.first)->GetDash() - dynamic_cast<Player*>(second.first)->GetDash();
				if (speed > 0) {
					// player2�𐁂���΂�
				}
				else if(speed < 0){
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
				Vector3D pos1 = capsule->pos;
				Vector3D pos2 = sphere->pos;
				Ball* ball = dynamic_cast<Ball*>(second.first);
				Player* player = dynamic_cast<Player*>(first.first);
				if (IsShoot) {
					// player1�𐁂���΂�
					Vector3D dirVec = pos1 - pos2;
					if (!player->GetIsKnockBack()) {
						player->SetKnockBack(250, dirVec);
					}
				}
				else {
					// �����΂�
					Vector3D dirVec = pos2 - pos1;
					ball->SetForwardVec(dirVec);

					/*float angle = Math::CalcVectorAngle(player->GetForwardVec(), ball->GetPos().Normalize());
					if (angle < Math::DegToRad(90)) {*/
						ball->SetSpeed(130);
					//}
				}
			}
		}
	}
	return true;
};

bool CollisionManager::CollisionCheckForSphere(std::pair<ObjectBase*, CollisionBase*>& first){

	Sphere* sphere1 = dynamic_cast<Sphere*>(first.second);

	// �L���X�g���s
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
				if (!ball->GetIsShoot()) {
					ball->SetSpeed(10 * power);
				}
				else {
					ball->AddSpeed(10 * (power/2));
				}
			}
		}
		else if (second.second->name == "goal") {
			
		}
	}
	return true;
};