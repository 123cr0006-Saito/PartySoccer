#include "../../Header/Mode/ModeGame.h"
#include "../../Header/Manager/ObjectManager.h"
#include "../../Header/Object/Stage/Stage.h"
#include "../../Header/Object/Stage/Ball.h"
#include "../../Header/Object/Stage/Goal.h"
#include "../../Header/Object/Stage/Wall.h"
#include "../../Header/Manager/RenderManager.h"
#include "../../Header/Manager/CollisionManager.h"
#include "../AppFrame/source/CFile/CFile.h"

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }
	// �}�l�[�W���[�̎擾
	_superManager = SuperManager::GetInstance();
	// �I�u�W�F�N�g�̐���
	LoadObject();
	// �J�����̐���
	_camera = NEW Camera();
	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();
	return true;
}

bool ModeGame::LoadObject(){
	// �I�u�W�F�N�g�̐���
	ObjectManager* objectManager = NEW ObjectManager();
	//�X�e�[�W�̐���
	objectManager->Add("Stage", NEW Stage("Stage"));
	//�{�[���̐���
	objectManager->Add("Ball", NEW Ball("Ball"));
	//�S�[���̐���
	std::vector<std::tuple<std::string, Vector3D, Vector3D>> goalList = LoadObjectParam("Data/GoalParam.csv");
	int count = 0;
	for (auto&& list : goalList) {
		std::string name = std::get<0>(list) + std::to_string(count + 1);
		Goal* goal = new Goal(name, std::get<1>(list), std::get<2>(list).Radian());
		objectManager->Add(name, goal);
		count++;
	}
	//�S�[���l�b�g�R���W�����̐���
	std::vector<std::tuple<std::string, Vector3D, Vector3D>> goalNetList = LoadObjectParam("Data/GoalNetParam.csv");
	for (auto&& list : goalNetList) {
		Wall* wall = NEW Wall();
		wall->SetName(std::get<0>(list));
		wall->SetColPos(std::get<1>(list));
		wall->SetColLength(std::get<2>(list));
		objectManager->Add(std::get<0>(list), wall);
	}
	//�ǃR���W�����̐���
	//std::vector<std::tuple<std::string, Vector3D, Vector3D>> wallList = LoadObjectParam("Data/WallParam.csv");
	//for (auto&& list : wallList) {
	//	Wall* wall = NEW Wall();
	//	wall->SetColPos(std::get<1>(list));
	//	wall->SetColLength(std::get<2>(list));
	//	objectManager->Add(std::get<0>(list), wall);
	//}
	

	// �}�l�[�W���[�ɓo�^
	_superManager->AddManager("objectManager", 1, objectManager);
	return true;
};

std::vector<std::tuple<std::string, Vector3D, Vector3D>> ModeGame::LoadObjectParam(std::string fileName) {
	std::vector<std::tuple<std::string, Vector3D, Vector3D>> nameList;
	// csv�t�@�C����ǂݍ���
	CFile file(fileName);
	// �t�@�C�����J�����ꍇ
	if (file.Success()) {
		int c = 0;
		const char* p = (const char*)file.Data();
		int size = file.Size();
		while (c < size) {
			std::string name;
			Vector3D pos,param;
			c += GetString(&p[c],&name); // ���O���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &pos.x); //x���W���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &pos.y); //y���W���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &pos.z); //z���W���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &param.x); //x�̒������擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &param.y); //y�̒������擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &param.z); //z�̒������擾
			c += SkipSpace(&p[c], &p[size]); // �󔒂�R���g���[���R�[�h���X�L�b�v����
			nameList.push_back(std::make_tuple(name,pos,param));
		}
	}
	else {
		DebugErrar();
	}
	return nameList;
};


bool ModeGame::Process() {
	base::Process();
	_superManager->Update();
	_camera->Update();
	return true;
}

bool ModeGame::Render() {
	base::Render();
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	_superManager->Draw();
	_camera->Draw();
	return true;
}
