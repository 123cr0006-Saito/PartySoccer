#include "../../Header/Manager/CollisionManager.h"
#include "../../AppFrame/source/Application/UtilMacro.h"
#include "../../AppFrame/source/System/Header/Collision/3DCollision.h"
#include "../../Header/Object/Stage/Ball.h"
#include "../../Header/Object/Stage/Wall.h"
#include "../../Header/Object/Player/Player.h"
#include "../../Header/Object/Stage/Goal.h"
#include "../AppFrame/source/Mode/ModeServer.h"
#include "../../Header/Mode/ModeGame.h"
#include "../../Header/Mode/ModeGoal.h"
#include "../AppFrame/MemoryLeak.h"
#include "../AppFrame/source/Application/Global.h"

CollisionManager::CollisionManager(){

};

CollisionManager::~CollisionManager(){
	_addCollisionList.clear();
	_delCollisionNameList.clear();
	_delCollisionList.clear();
	_collisionList.clear();
};

bool CollisionManager::Terminate() {
	return true;
}

void CollisionManager::Add(CollisionBase* collision){
	_addCollisionList.emplace_back(collision);
};

void CollisionManager::AddInput(void* value){
	CollisionBase* collision = static_cast<CollisionBase*>(value);
	_addCollisionList.emplace_back(collision);
};

void  CollisionManager::DeleteName(std::string name){
	_delCollisionNameList.emplace_back(name);
};

void CollisionManager::DeleteInput(void* value){
	CollisionBase* collision = static_cast<CollisionBase*>(value);
	_delCollisionList.emplace_back(collision);
};

void CollisionManager::DelAll(){
	for(auto&& list : _addCollisionList){
		delete list;
	}
	for (auto&& list : _collisionList) {
		delete list;
	}
	_collisionList.clear();
	_addCollisionList.clear();
};

int CollisionManager::GetListSize() {
	return _collisionList.size();
};

bool CollisionManager::UpdateInit(){
	// deleteList�̒��ɒl������Ƃ��폜
	for (auto list : _delCollisionList) {
		for (auto itr = _collisionList.begin(); itr != _collisionList.end();) {
			if ((*itr) == list) {
				delete (*itr);
				itr = _collisionList.erase(itr);
			}
			else {
				++itr;
			}
		}
	}

	for (auto list : _delCollisionNameList) {
		for (auto itr = _collisionList.begin(); itr != _collisionList.end();) {
			if ((*itr)->GetName() == list) {
				delete (*itr);
				itr = _collisionList.erase(itr);
			}
			else{
				++itr;
			}
		}
	}

	// addList�̒��ɒl������Ƃ��ǉ�
	for (auto list : _addCollisionList) {
		_collisionList.emplace_back(list);
	}

	// addList��deleteList���N���A
	_addCollisionList.clear();
	_delCollisionNameList.clear();
	_delCollisionList.clear();
	return true;
};

bool CollisionManager::Update(){
	
	UpdateInit();

	// �R���W������������O�̏�����
	for (auto&& first : _collisionList) {
		// �O��̔��茋�ʂ�ۑ�
		first->isHitOld = first->isHit;
		// ���茋�ʂ�������
		first->isHit = false;
	}

	// �Փ˔���
	for(auto&& first :_collisionList){
		std::vector<std::string> name = { "shoot", "goal","wall","GoalNet"};
		auto itr = std::find_if(name.begin(), name.end(),[=](std::string temp){
			return temp == first->GetName();
		});

		if (itr != name.end()) {
			// name�ɏ����Ă�����̂�ball�݂̂Ɣ�����s������ball�̂ق��ŏ���������
			continue;
		}

		if(first->GetName() == "player"){
			CollisionCheckForCapsule(first);
		}
		else if(first->GetName() == "ball"){
			CollisionCheckForSphere(first);
		}
	}
	return true;
};

bool CollisionManager::Draw(){
#ifdef _DEBUG
	for (auto&& list : _collisionList) {
		list->Render(0xff0000);
	}
#endif
	return true;
};

bool CollisionManager::CollisionCheckForCapsule(CollisionBase* first){

	Capsule* capsule1 = dynamic_cast<Capsule*>(first);

	// �L���X�g���s
	if(!capsule1){
		DebugErrar();
		return false;
	}

	for (auto&& second : _collisionList) {

		if (first == second)continue;
		if (second->GetName() == "shoot" || second->GetName() == "goal")continue;

		if(second->GetName() == "player"){
			// �������O�̃I�u�W�F�N�g���m�͔�����s��Ȃ�

			Capsule* capsule2 = dynamic_cast<Capsule*>(second);
			// �L���X�g���s
			if (!capsule2) {
				DebugErrar();
				return false;
			}

			if (Collision3D::TwoCapsuleCol((*capsule1), (*capsule2))) {
				//�Փˏ���
				Player* player1 = dynamic_cast<Player*>(first->GetObje());
				if (!player1) {
					DebugErrar();
				}
				Player* player2 = dynamic_cast<Player*>(second->GetObje());
				if (!player2) {
					DebugErrar();
				}
				first->isHit = second->isHit = true;
				if (player1->GetDash() > player2->GetDash()) {
					// player2�𐁂���΂�
					Vector3D dirVec = capsule2->up_pos - capsule1->pos;
					if (!player2->GetIsKnockBack()) {
						global._soundServer->DirectPlay("SE_KnockBack");
						player2->SetKnockBack(150, dirVec);
					}
				}
			}
		}
		else if (second->GetName() == "ball") {
			Sphere* sphere = dynamic_cast<Sphere*>(second);
			// �L���X�g���s
			if (!sphere) {
				DebugErrar();
				return false;
			}

			if (Collision3D::SphereCapsuleCol((*sphere),(*capsule1))) {
				//�Փˏ���		
				Ball* ball = dynamic_cast<Ball*>(second->GetObje());
				if (!ball) {
					DebugErrar();
				}
				bool IsShoot = ball->GetIsShoot();
				Vector3D pos1 = capsule1->pos;
				Vector3D pos2 = sphere->pos;
				Player* player = dynamic_cast<Player*>(first->GetObje());
				if (!player) {
					DebugErrar();
				}
				first->isHit = second->isHit = true;
				if (IsShoot) {
					// player1�𐁂���΂�
					Vector3D dirVec = pos1 - pos2;
					if (!player->GetIsKnockBack()) {
						global._soundServer->DirectPlay("SE_KnockBack");
						player->SetKnockBack(250, dirVec);
					}
				}
				else {
					// �����΂�
					Vector3D dirVec = pos2 - pos1;
					ball->SetForwardVec(dirVec);

					Vector3D forwardVec = player->GetForwardVec();
					Vector3D ballVec = ball->GetPos() - player->GetPos();
					float angle = Math::CalcVectorAngle(forwardVec, ballVec.Normalize());
					// ���ʂ���Ԃ������Ƃ������X�s�[�h���グ��
					if (angle < Math::DegToRad(90)) {
						global._soundServer->DirectPlay("SE_Dribble");
						ball->SetSpeed(130);
					}
				}
			}
		}
	}

	// �ǂ̔��� �ǂ͕��ʂ̓����蔻��ōl����
	Player* player = dynamic_cast<Player*>(first->GetObje());
	if (!player) {
		DebugErrar();
	}
	auto PositionLimit = [](float& pos, int max, int min) {
		if (pos < min) pos = min;
		else if (pos > max) pos = max;
	};
	Vector3D pos = capsule1->pos;
	PositionLimit(pos.x, 6335, -6335);
	PositionLimit(pos.z, 4876, -3180);
	player->SetPos(pos);

	return true;
};

bool CollisionManager::CollisionCheckForSphere(CollisionBase* first){

	Sphere* sphere1 = dynamic_cast<Sphere*>(first);

	// �L���X�g���s
	if (!sphere1) {
		DebugErrar();
		return false;
	}
	bool isHitGoalNet = false;
	for (auto&& second : _collisionList) {
		if (second->GetName() == "player") {
			first->isHit = second->isHit = true;
		}
		else if (second->GetName() == "shoot") {
			Sphere* sphere2 = dynamic_cast<Sphere*>(second);
			if (!sphere2) {
				DebugErrar();
				return false;
			}
			if (Collision3D::SphereCol((*sphere1), (*sphere2))) {
				Vector3D pos1 = sphere1->pos;
				Vector3D pos2 = sphere2->pos;
				Vector3D dirVec =  pos1 - pos2;
				Ball* ball = dynamic_cast<Ball*>(first->GetObje());
				if (!ball) {
					DebugErrar();
					return false;
				}
				Player* player = dynamic_cast<Player*>(second->GetObje());
				if (!player) {
					DebugErrar();
					return false;
				}
				first->isHit = second->isHit = true;
				global._soundServer->DirectPlay("SE_Shoot");
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
		else if (second->GetName() == "goal") {
			OBB* obb = dynamic_cast<OBB*>(second);
			if (!obb) {
				DebugErrar();
				return false;
			}
			if (Collision3D::OBBSphereCol((*obb), (*sphere1) )) {
				first->isHit = second->isHit = true;
				if(second->isHitOld)continue;
				Ball* ball = dynamic_cast<Ball*>(first->GetObje());
				if (!ball) {
					DebugErrar();
					return false;
				}
				Goal* goal = dynamic_cast<Goal*>(second->GetObje());
				if (!goal) {
					DebugErrar();
					return false;
				}
				ModeServer* modeServer = ModeServer::GetInstance();
				if (!modeServer->Search("ModeGoal")){
					global._soundServer->DirectPlay("SE_Whistle");
					global._soundServer->DirectPlay("SE_Cheers");
					modeServer->Add(NEW ModeGoal(goal->GetName()),1000,"ModeGoal");
				}
			}		
		}
		else if(second->GetName() == "wall" && !isHitGoalNet){
			OBB* obb = dynamic_cast<OBB*>(second);
			if (!obb) {
				DebugErrar();
				return false;
			}
			Vector3D hitPos;
			if (Collision3D::OBBSphereCol((*obb), (*sphere1),&hitPos)) {
				Ball* ball = dynamic_cast<Ball*>(first->GetObje());
				if (!ball) {
					DebugErrar();
					return false;
				}
				Wall* wall = dynamic_cast<Wall*>(second->GetObje());
				first->isHit = second->isHit = true;
				if (!wall) {
					DebugErrar();
					return false;
				}
				global._soundServer->DirectPlay("SE_Bound");
				//�����o������
				Vector3D correctionVector = ball->GetPos() - hitPos;
				ball->SetPos(ball->GetPos() + correctionVector.Normalize() * (sphere1->r - correctionVector.Len()));
				// ���ˏ���
				ball->SetForwardVec(Reflect(ball->GetForwardVec(), correctionVector.Normalize()));
				// ���ˎ��X�s�[�h���Z
				ball->AddSpeed(10);
			}
		}
		else if (second->GetName() == "GoalNet") {
			OBB* obb = dynamic_cast<OBB*>(second);
			Vector3D hitPos;
			if (Collision3D::OBBSphereCol((*obb), (*sphere1), &hitPos)) {
				Ball* ball = dynamic_cast<Ball*>(first->GetObje());
				if (!ball) {
					DebugErrar();
					return false;
				}
				Wall* wall = dynamic_cast<Wall*>(second->GetObje());
				first->isHit = second->isHit = true;
				if (!wall) {
					DebugErrar();
					return false;
				}
				ball->SetPosToOldPos();
				ball->AddSpeed(2); // �S�[���l�b�g�ɓ��������Ƃ���]���Ȃ���~�܂��Ăق����̂ŃX�s�[�h�������Z����
				isHitGoalNet = true;
			}
		}
	}
	// �����Ă͂����Ȃ��̈�𒴂����Ƃ��̏���
	Vector3D pos1 = sphere1->pos;
	Vector3D normal = Vector3D(0, 0, 0);

	if (pos1.z < -3180) {
		normal = Vector3D(0, 0, 1);
		pos1.z = -3180;
	}
	else if (pos1.z > 4876) {
		normal = Vector3D(0, 0, -1);
		pos1.z = 4876;
	}
	else if (pos1.x < -7500) {
		normal = Vector3D(1, 0, 0);
		pos1.x = -7500;
	}
	else if (pos1.x > 7500) {
		normal = Vector3D(-1, 0, 0);
		pos1.x = 7500;
	}

	// �ǂɓ��������Ƃ��̏���
	if(normal.Sqlen() > 0){
		Ball* ball = dynamic_cast<Ball*>(first->GetObje());
		ball->SetForwardVec(Reflect(ball->GetForwardVec(), normal));
		ball->SetPos(pos1);
		ball->AddSpeed(10);
	}

	return true;
};