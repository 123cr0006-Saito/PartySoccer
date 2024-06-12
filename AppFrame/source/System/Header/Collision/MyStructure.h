#pragma once
#include "dxlib.h"
#include "../Function/Vector3D.h"
#include <vector>
#include <string>

// �~����
#define	PI				(3.141592653589793)

// RECT�p�\����
struct MYRECT {
	float		x, y, w, h;
};

// RECT�p�\����+�A���t�@
struct MYRECT_PLUS : public MYRECT{
	float cx, cy;
	float direction;
};

struct MYCIRCLE {
	float x, y;
	float r;
};

struct HITSLIDE {
	int	hit;				// �������Ă����1�A�������Ă��Ȃ������0
	int	slide_x, slide_y;	// �������Ă���ꍇ�A���炷�ׂ��l
	int index;
};

struct POINT_LINE_SHORT {
	Vector3D hit_point;
	float length = 0.0f;
	float coefficient = 0.0f;//�x�N�g���W��
};

struct TWOLINE_SHORT {
	Vector3D line_1_point;
	Vector3D line_2_point;
	float line_1_coefficient = 0.0f;
	float line_2_coefficient = 0.0f;
	float length = 0.0f;
};

class CollisionBase
{
public:
	CollisionBase() { name = ""; };
	virtual ~CollisionBase() {};
	void SetName(std::string name) { this->name = name; }
	virtual void Render(unsigned int color) =0;
	std::string GetName() { return name; }
	Vector3D pos;
	std::string name;
};

class Sphere : public CollisionBase
{
public:
	Sphere() : CollisionBase(){
		pos = VGet(0.0f, 0.0f, 0.0f);
		r = 0.0f;
	}
	Sphere(Vector3D pos, float r) : CollisionBase() {
		pos = pos;
		this->r = r;
	}

	// �`�揈��
	void Render(unsigned int color)override;

	float r;
};

class OBB : public CollisionBase
{
public:
	OBB() : CollisionBase() {
		// ������Ԃł̓��[���h�̎��ƕ��s�ȏ�Ԃɂ���iAABB�j
		dir_vec[0] = Vector3D(1.0f, 0.0f, 0.0f);
		dir_vec[1] = Vector3D(0.0f, 1.0f, 0.0f);
		dir_vec[2] = Vector3D(0.0f, 0.0f, 1.0f);

		for (int i = 0; i < 3; ++i) {			
			length[i] = 0.0f;
		}
	}

	void SetLength(Vector3D value) {
		length[0] = value.x;
		length[1] = value.y;
		length[2] = value.z;
	}

	// ��]����
	// x��->y��->z���̏��Ԃ�, �e������]������
	void Rotate(Vector3D vRot);

	// ���_���W�̎擾
	void GetVertexPos(std::vector<Vector3D>& vertexPosList);

	// �`�揈��
	void Render(unsigned int color)override;

	Vector3D dir_vec[3];//xv,yv,zv
	float length[3]; //0:w 1:h 3:d
};

class Capsule : public CollisionBase {
public:
	Capsule() : CollisionBase() {
		up = 0.0f;
		r = 0.0f;
		for (int i = 0; i < 3; i++) {
			direction[i] = 0;
		}
	};

	void Update() {
		up_pos = pos + Vector3D(0,up,0);
	};

	// �`�揈��
	void Render(unsigned int color)override;

	Vector3D up_pos;
	float up = 0.0f;
	float r = 0.0f;
	float direction[3] = { 0.0f,0.0f, 0.0f };
};