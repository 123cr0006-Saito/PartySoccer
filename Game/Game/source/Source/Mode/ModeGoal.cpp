//----------------------------------------------------------------------
// @filename ModeGoal.cpp
// @author: saito ko
// @explanation
// �S�[�����̉��o���s���N���X
//----------------------------------------------------------------------
#include "../../Header/Mode/ModeGoal.h"
#include "../AppFrame/source/Mode/ModeServer.h"
#include "../../Header/Other/Score.h"
#include "../AppFrame/source/CFile/CFile.h"
#include "../AppFrame/source/Application/UtilMacro.h"
#include "../AppFrame/MemoryLeak.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/UIManager.h"
#include "../../Header/Mode/ModeGame.h"
#include "../../Header/Other/TimeLimit.h"
#include "../../Header/UI/Score/UIScore.h"
#include "../../Header/UI/Animation/LocationAnim.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param ���_����ꂽ�`�[���̖��O
// @return ����
//----------------------------------------------------------------------
ModeGoal::ModeGoal(const std::string& name){
	TimeLimit::GetInstance()->Stop();
	_score = Score::GetInstance();
	_superManager = SuperManager::GetInstance();
	//�_���̎擾
	for(int i = 0; i < 2; i++){
		_nowScore[i] = _score->GetScore("Goal_" + std::to_string(i+1));
	}
	//���_��ǉ�
	_score->AddScore(name,1);
	_name = name;
	_currentTime = 0;
	//UI�̓ǂݍ���
	LoadUI();
	//�_���̉摜��ǂݍ���
	for(int i = 0; i < 10; i++){
		std::string num = std::to_string(i);
		_numHandle[i] = ResourceServer::LoadGraph("Score_" + num, ("Res/UI/Number/timer_0" + num + ".png").c_str());
	}
	//UI��ǉ�
	for(auto&& list : _ui){
		_superManager->GetManager("uiManager")->Add(list.second);

		// �`�[���̓��_��ݒ�
		if(list.first == "Goal_1"){
			list.second->SetHandle(_numHandle[_nowScore[0]]);
		}
		else if(list.first == "Goal_2"){
			list.second->SetHandle(_numHandle[_nowScore[1]]);
		}
	}

};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
ModeGoal::~ModeGoal(){
	_score = nullptr;
};
//----------------------------------------------------------------------
// @brief ����������
// @return ����
//----------------------------------------------------------------------
bool ModeGoal::Initialize(){
	_currentTime = GetNowCount();
	return true;
};
//----------------------------------------------------------------------
// @brief UI�̓ǂݍ���
// @return ����
//----------------------------------------------------------------------
void ModeGoal::LoadUI(){
	int count = 0;
	CFile file("Data/GoalUIParam.csv");
	// �t�@�C�����J�����ꍇ
	if (file.Success()) {
		int c = 0;
		const char* p = (const char*)file.Data();
		int size = file.Size();
		while (c < size) {
			std::string name, handlePath, animPath;
			int handle;
			Vector3D pos, center, extrate;
			float angle, alpha;
			c += GetString(&p[c], &name); // �^�O���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetString(&p[c], &handlePath); // �摜�t�@�C�������擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetString(&p[c], &animPath); // �A�j���[�V�����t�@�C�������擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &pos.x); //x���W���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &pos.y); //y���W���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &center.x); //���S���p���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &center.y); //���S���p���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &extrate.x); //x�g�嗦���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &extrate.y); //y�g�嗦���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &angle); //��]�����擾
			c += SkipSpace(&p[c], &p[size]); // �󔒂�R���g���[���R�[�h���X�L�b�v����

			handle = ResourceServer::LoadGraph(name,handlePath.c_str());
			alpha = 255;
			//UI�N���X�̍쐬
			UIRotaBase* ui = NEW UIRotaBase(name, pos, center, extrate, angle, alpha, handle,10000+count);
			if (animPath != "") {
				//�A�j���[�V�����̓ǂݍ���
				LocationAnim* anim = NEW LocationAnim(ui, animPath);
				ui->SetAnimation(anim);
			}

			if(_name == name){
				//�S�[�������`�[���͕ʂ̃A�j���[�V������ǉ��ǂݍ���
				LocationAnim* anim = NEW LocationAnim(ui, "Data/Goal/AddScoreAnimation.csv");
				ui->SetAnimation(anim);
			}

			_ui.emplace_back(name,ui);
			count++;
		}
	}
	else {
		DebugError();
	}
};
//----------------------------------------------------------------------
// @brief �I������
// @return �������Ă��邩
//----------------------------------------------------------------------
bool ModeGoal::Terminate(){
	for (auto&& list : _ui) {
		_superManager->GetManager("uiManager")->DeleteName(list.first);
	}
	return true;
};
//----------------------------------------------------------------------
// @brief �X�V����
// @return �����������ǂ���
//----------------------------------------------------------------------
bool ModeGoal::Process(){
	AnimationProcess();
	return true;
};
//----------------------------------------------------------------------
// @brief �A�j���[�V�����̍X�V����
// @return �����������ǂ���
//----------------------------------------------------------------------
void ModeGoal::AnimationProcess(){
	int nowTime = GetNowCount() - _currentTime;

	// �����ɃA�j���[�V��������������
	// 1.8�b
	nowTime -= 1800;
	if (nowTime < 0)return;

	// 1.8�b��A�_���̉摜���X�V
	for(auto&& list : _ui){
		if(list.first == _name){
			list.second->SetHandle(_numHandle[_score->GetScore(_name)]);
		}
	}
	//3.3�b
	nowTime -= 1500;
	if (nowTime < 0)return;
	//�A�j���[�V�������I�������̂ō폜
	if(nowTime > 0){
		ModeServer::GetInstance()->Del(this);
		//���W���Ԃ�������
		dynamic_cast<ModeGame*>(ModeServer::GetInstance()->Get("ModeGame"))->ReSetGame();
	}
};
//----------------------------------------------------------------------
// @brief �`�揈��
// @return �����������ǂ���
//----------------------------------------------------------------------
bool ModeGoal::Render(){
	return true;
};