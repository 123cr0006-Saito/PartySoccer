#pragma once
#include "MyStructure.h"
#include "../../Header/Collision/2DCollision.h"
#include"dxlib.h"
class Collision3D
{
public:

	//�ŒZ�����͑�̓_�Ɠ_�𐂒��ɉ��������ɂȂ�

	//���ʏ�ł̎l�p���m�̂����蔻��
	static bool PlaneCollision(Vector3D pos1, float w1, float d1, Vector3D pos2, float w2, float d2);

	//AABB�̓����蔻��
	static bool AABBCollision(Vector3D pos1, float w1, float h1, float d1, Vector3D pos2, float w2, float h2, float d2);

	//���ʏ�ł̉~�̂����蔻��
	static bool CircleCollision(Vector3D pos1, float r1, Vector3D pos2, float r2);

	//�~���̓����蔻��
	static bool CylindCollision(Vector3D pos1, float r1,float h1, Vector3D pos2, float r2,float h2);

	//AABB�̍ŒZ����
	static float AABBShortLength(Vector3D Box, float wide, float height, float depth, Vector3D Point);

	//OBB���m�̓����蔻��
	static bool OBBCollision(OBB box_1,OBB box_2);

    //�_�ƒ����̍ŒZ����
	static POINT_LINE_SHORT PointLineShortLength(Vector3D line_start, Vector3D line_end, Vector3D point);

	//�_�Ɛ����̍ŒZ����   ���I�ȍ��͎n�_�ƏI�_�̓��[���h���W�œ����
	static POINT_LINE_SHORT PointLineSegShortLength(Vector3D line_start, Vector3D line_end, Vector3D point);

	//2�����̐����ɂȂ�ꏊ�ƃx�N�g���W��
	static TWOLINE_SHORT TwoLineShortPoint(Vector3D line_1_start, Vector3D line_1_end, Vector3D line_2_start, Vector3D line_2_end);

	//2�����̐����ɂȂ�ꏊ�ƃx�N�g���W��
	static TWOLINE_SHORT TwoSegmentShortPoint(Vector3D line_1_start, Vector3D line_1_end, Vector3D line_2_start, Vector3D line_2_end);

	//���Ƌ��̓����蔻��
	static bool SphereCol(Vector3D pos1, float r1, Vector3D pos2, float r2);
	static bool SphereCol(const Sphere& sphere1, const Sphere& sphere2);

	//�J�v�Z�����m�̓����蔻��
	static bool TwoCapsuleCol(Vector3D line_1_start, Vector3D line_1_end, float r_1, Vector3D line_2_start, Vector3D line_2_end, float r_2);
	static bool TwoCapsuleCol(const Capsule& capsule1, const Capsule& capsule2);

	// ���ƃJ�v�Z���̓����蔻��
	static bool SphereCapsuleCol(Vector3D spherePos, float sphereR, Vector3D capsuleStartPos, Vector3D capsuleEndPos, float capsuleR, Vector3D* shortestPos = nullptr);
	static bool SphereCapsuleCol(const Sphere& sphere, const Capsule& capsule, Vector3D* shortestPos = nullptr);

	//�_�Ƃn�a�a�̍Őڋߓ_�@OBB�Ɠ_����ԋ߂�OBB�̈ʒu��Ԃ��܂��B
	static  Vector3D PointOBB(Vector3D point, OBB obb);
	
	//OBB�Ƌ��̓����蔻��
	static bool OBBSphereCol(OBB obb, Vector3D point, float r, Vector3D* hitPos = nullptr);
	static bool OBBSphereCol(const OBB& obb, const Sphere& sphere, Vector3D* hitPos = nullptr);

	//OBB�ƃJ�v�Z���̓����蔻��
	static bool OBBCapsuleCol(OBB obb, Vector3D line_start, Vector3D line_end, float r, Vector3D* hitPos = nullptr);
	//�I�[�o�[���[�h
	static bool OBBCapsuleCol(OBB obb, Capsule capsule, Vector3D* hitPos = nullptr);

};