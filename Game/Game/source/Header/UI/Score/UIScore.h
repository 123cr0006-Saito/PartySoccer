//----------------------------------------------------------------------
// @filename UIScore.h
// @author: saito ko
// @explanation
// �X�R�A��`�悷��UI�N���X
//----------------------------------------------------------------------
#pragma once
#include "../Base/UIRotaBase.h"
#include <array>
class UIScore : public UIRotaBase
{
public:
	UIScore(const Vector3D& pos,const std::string& name,class Score* score);
	virtual ~UIScore();
	virtual void Update()override;
	virtual void Draw()override;
protected:
	class Score* _score;//�X�R�A�N���X
	std::string _teamName;//�`�[����
	std::array<int, 10> _scoreHandle;//�X�R�A�̃n���h��
};