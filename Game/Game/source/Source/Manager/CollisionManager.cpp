#include "../../Header/Manager/CollisionManager.h"
#include "../../AppFrame/source/Application/UtilMacro.h"
#include "../../AppFrame/source/System/Header/Collision/3DCollision.h"
#include "../../Header/Object/Stage/Ball.h"
#include "../../Header/Object/Stage/Wall.h"
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
		std::vector<std::string> name = { "shoot", "goal","wall","GoalNet"};
		auto itr = std::find_if(name.begin(), name.end(),[=](std::string temp){
			return temp == first.second->name;
		});

		if (itr != name.end()) {
			// nameに書いてあるものはballのみと判定を行うためballのほうで処理をする
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

bool CollisionManager::Draw(){
	for (auto&& list : _collisionList) {
		list.second->Render(0xff0000);
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
				Player* player = dynamic_cast<Player*>(first.first);
				if (IsShoot) {
					// player1を吹き飛ばす
					Vector3D dirVec = pos1 - pos2;
					if (!player->GetIsKnockBack()) {
						player->SetKnockBack(250, dirVec);
					}
				}
				else {
					// 球を飛ばす
					Vector3D dirVec = pos2 - pos1;
					ball->SetForwardVec(dirVec);

					Vector3D forwardVec = player->GetForwardVec();
					Vector3D ballVec = ball->GetPos() - player->GetPos();
					float angle = Math::CalcVectorAngle(forwardVec, ballVec.Normalize());
					// 正面からぶつかったときだけスピードを上げる
					if (angle < Math::DegToRad(90)) {
						ball->SetSpeed(130);
					}
				}
			}
		}
	}

	// 壁の判定 壁は平面の当たり判定で考える
	Player* player = dynamic_cast<Player*>(first.first);
	auto PositionLimit = [](float& pos, int max, int min) {
		if (pos < min) pos = min;
		else if (pos > max) pos = max;
	};
	Vector3D pos = capsule->pos;
	PositionLimit(pos.x, 6335, -6335);
	PositionLimit(pos.z, 4876, -3180);
	player->SetPos(pos);

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
		else if(second.second->name == "wall"){
			OBB* obb = dynamic_cast<OBB*>(second.second);
			Vector3D hitPos;
			if (Collision3D::OBBSphereCol((*obb), (*sphere1),&hitPos)) {
				Ball* ball = dynamic_cast<Ball*>(first.first);
				Wall* wall = dynamic_cast<Wall*>(second.first);
				if (!wall) {
					DebugErrar();
					return false;
				}
				ball->SetForwardVec(Reflect(ball->GetForwardVec(),(hitPos - ball->GetPos()).Normalize()));
				ball->AddSpeed(10);
			}
		}
		else if (second.second->name == "GoalNet") {
			OBB* obb = dynamic_cast<OBB*>(second.second);
			Vector3D hitPos;
			if (Collision3D::OBBSphereCol((*obb), (*sphere1), &hitPos)) {
				Ball* ball = dynamic_cast<Ball*>(first.first);
				Wall* wall = dynamic_cast<Wall*>(second.first);
				if (!wall) {
					DebugErrar();
					return false;
				}
				ball->SetPosToOldPos();
				ball->AddSpeed(2); // ゴールネットに当たったとき回転しながら止まってほしいのでスピード少し加算する
			}
		}
	}
	// 壁の判定 壁は平面の当たり判定で考える
	Vector3D pos1 = sphere1->pos;
	Vector3D normal = Vector3D(0, 0, 0);

	if (pos1.z < -3180) {
		normal = Vector3D(0, 0, 1);
	}
	else if (pos1.z > 4876) {
		normal = Vector3D(0, 0, -1);
	}
	// 壁に当たったときの処理
	if(normal.Sqlen() > 0){
		Ball* ball = dynamic_cast<Ball*>(first.first);
		ball->SetForwardVec(Reflect(ball->GetForwardVec(), normal));
		ball->AddSpeed(10);
	}

	return true;
};