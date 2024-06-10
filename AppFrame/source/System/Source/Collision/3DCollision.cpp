#include "../../Header/Collision/3DCollision.h"

bool Collision3D::PlaneCollision(Vector3D pos1, float w1,float d1, Vector3D pos2, float w2, float d2)
{
	Vector3D receiv = pos1 - Vector3D(w1 / 2, 0, d1 / 2);
	Vector3D give = pos2 - Vector3D(w2 / 2, 0, d2 / 2);

	return Collision2D::IsHitBox(receiv.x, receiv.z, w1, d1, give.x, give.z, w2, d2);
}

bool Collision3D::AABBCollision(Vector3D pos1, float w1, float h1, float d1, Vector3D pos2, float w2, float h2, float d2)
{
	Vector3D receiv = pos1 - Vector3D(w1 / 2, h1 / 2, d1 / 2);
	Vector3D give = pos2 - Vector3D(w2 / 2, h2 / 2, d2 / 2);

	if(Collision2D::IsHitBox(receiv.x, receiv.z, w1, d1, give.x, give.z, w2, d2)) {
		if(Collision2D::IsHitBox(receiv.x, receiv.y, w1, h1, give.x, give.y, w2, h2)) {
			return true;
		}
	}

	return false;
}

bool Collision3D::CircleCollision(Vector3D pos1, float r1, Vector3D pos2, float r2){
	Vector3D col = pos1 - pos2; col.y = 0;
	float r = r1 + r2;
	if (r * r > col.x * col.x + col.z * col.z) {
		return true;
	}
	return false;
}

bool Collision3D::CylindCollision(Vector3D pos1, float r1, float h1, Vector3D pos2, float r2, float h2) {
	Vector3D col = pos1 - pos2;
	float r = r1 + r2;
	if (r * r > col.x * col.x + col.z * col.z) {
		if (pos1.y < pos2.y && pos1.y + h1 > pos2.y ||
			pos1.y < pos2.y + h2 && pos1.y + h1 > pos2.y + h2) {
			return true;
		}
	}
	return false;
}

float Collision3D::AABBShortLength(Vector3D Box, float wide, float height ,float depth , Vector3D Point) {
	float SqLen = 0;   // �����ׂ̂���̒l���i�[
	float point[3] = { Point.x,Point.y,Point.z};
	float box[3] = { Box.x,Box.y,Box.z };
	float length[3] = { wide/2,height/2,depth/2 };

	for (int i = 0; i < 3; i++)
	{
		// �e���œ_���ŏ��l�ȉ��������͍ő�l�ȏ�Ȃ�΁A�����l��
		if (point[i] < box[i] - length[i])  // i=0��X�A1��Y�A2��Z�̈Ӗ��ł�
			SqLen += ((point[i] - (box[i] - length[i])) * (point[i] - (box[i] - length[i])));
		if (point[i] > box[i] + length[i])
			SqLen += ((point[i] - (box[i] + length[i])) * (point[i] - (box[i] + length[i])));
	}
	return sqrt(SqLen);
}

bool Collision3D::OBBCollision(OBB obb_1, OBB obb_2) {
	// length�͑S�̂̒����Ȃ̂Ŏg���Ƃ��͔����ɂ���
	//NAe �� �����x�N�g�� Ae �� �����x�N�g���ɂ��̒��������������́@�����x�N�g���̓}�g���N�X���玝���Ă������̂Ő��K������Ă���

	Vector3D NAe1 = obb_1.dir_vec[0], Ae1 = NAe1 * (obb_1.length[0] / 2);
	Vector3D NAe2 = obb_1.dir_vec[1], Ae2 = NAe2 * (obb_1.length[1] / 2);
	Vector3D NAe3 = obb_1.dir_vec[2], Ae3 = NAe3 * (obb_1.length[2] / 2);
	Vector3D NBe1 = obb_2.dir_vec[0], Be1 = NBe1 * (obb_2.length[0] / 2);
	Vector3D NBe2 = obb_2.dir_vec[1], Be2 = NBe2 * (obb_2.length[1] / 2);
	Vector3D NBe3 = obb_2.dir_vec[2], Be3 = NBe3 * (obb_2.length[2] / 2);
	//Misalignment�ł��Ȃ��̒��S�Ƀ��f�������炵�Ă��� ��̂��������ōςނƎv�����t���C�g�n�Ȃǂ�3����]������Ƃ���
	//VTransform�̒��̉�]�s���y�������łȂ����Ƃ����܂߂�3���ŉ�]���Ă�������
	Vector3D Interval = obb_1.pos - obb_2.pos;

	//  �e���̕����x�N�g���ƕ������Ƃ̐�Βl�̓��ς̘a���܂Ƃ߂����̂� ���S�_�Ԃ̋������r�����S�_�ԋ������Z��������Փ˂��Ă���

	// ������ : Ae1
	float rA = Ae1.Len();
	float rB = Math::LenSegOnSeparateAxis(NAe1, Be1, Be2, Be3);
	float L = fabs(Interval.Dot(NAe1));
	if (L > rA + rB)
		return false; // �Փ˂��Ă��Ȃ�

	// ������ : Ae2
	rA = Ae2.Len();
	rB = Math::LenSegOnSeparateAxis(NAe2, Be1, Be2, Be3);
	L = fabs(Interval.Dot(NAe2));
	if (L > rA + rB)
		return false;

	// ������ : Ae3
	rA = Ae3.Len();
	rB = Math::LenSegOnSeparateAxis(NAe3, Be1,Be2,Be3);
	L = fabs(Interval.Dot(NAe3));
	if (L > rA + rB)
		return false;

	// ������ : Be1
	rA = Math::LenSegOnSeparateAxis(NBe1, Ae1, Ae2, Ae3);
	rB = Be1.Len();
	L = fabs(Interval.Dot(NBe1));
	if (L > rA + rB)
		return false;

	// ������ : Be2
	rA = Math::LenSegOnSeparateAxis(NBe2, Ae1, Ae2, Ae3);
	rB = Be2.Len();
	L = fabs(Interval.Dot(NBe2));
	if (L > rA + rB)
		return false;

	// ������ : Be3
	rA = Math::LenSegOnSeparateAxis(NBe3, Ae1, Ae2, Ae3);
	rB = Be3.Len();
	L = fabs(Interval.Dot(NBe3));
	if (L > rA + rB)
		return false;

	// ��9���̌v�Z�͏�̕����x�N�g�������ł��ł���
	//  OBB���ӓ��m�Ђ˂����֌W�ŋ߂Â��ƕ����x�N�g���̕������ł͔���ł��Ȃ��Ȃ邻���ł�

	// ������ : C11   Ae1*Be1�ɐ���
	Vector3D Cross;
	Cross = NAe1.Cross(NBe1);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae2, Ae3);
	rB = Math::LenSegOnSeparateAxis(Cross, Be2, Be3);
	L = fabs(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// ������ : C12   Ae1*Be2
	Cross = NAe1.Cross(NBe2);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae2, Ae3);
	rB = Math::LenSegOnSeparateAxis(Cross, Be1, Be3);
	L = fabs(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// ������ : C13   Ae1*Be3
	Cross = NAe1.Cross(NBe3);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae2, Ae3);
	rB = Math::LenSegOnSeparateAxis(Cross, Be1, Be2);
	L = fabs(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// ������ : C21   Ae2*Be1
	Cross = NAe2.Cross(NBe1);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae1, Ae3);
	rB = Math::LenSegOnSeparateAxis(Cross, Be2, Be3);
	L = fabs(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// ������ : C22   Ae2*Be2
	Cross = NAe2.Cross(NBe2);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae1, Ae3);
	rB = Math::LenSegOnSeparateAxis(Cross, Be1, Be3);
	L = fabs(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// ������ : C23   Ae2*Be3
	Cross = NAe2.Cross(NBe3);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae1, Ae3);
	rB = Math::LenSegOnSeparateAxis(Cross, Be1, Be2);
	L = fabs(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// ������ : C31   Ae3*Be1
	Cross = NAe3.Cross(NBe1);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae1, Ae2);
	rB = Math::LenSegOnSeparateAxis(Cross, Be2, Be3);
	L = fabs(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// ������ : C32   Ae3*Be2
	Cross = NAe3.Cross(NBe2);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae1, Ae2);
	rB = Math::LenSegOnSeparateAxis(Cross, Be1, Be3);
	L = fabs(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// ������ : C33   Ae3*Be3
	Cross = NAe3.Cross(NBe3);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae1, Ae2);
	rB = Math::LenSegOnSeparateAxis(Cross, Be1, Be2);
	L = fabs(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
	return true;
}

//�ŒZ�����͑�̓_�Ɠ_�𐂒��ɉ��������ɂȂ�
//�_�ƒ����̍ŒZ����
POINT_LINE_SHORT Collision3D::PointLineShortLength(Vector3D line_start, Vector3D line_end, Vector3D point) {
	POINT_LINE_SHORT Re;
	Vector3D line = line_end - line_start;
	float length = line.Sqlen();

	Re.coefficient = 0.0f;
	if (length > 0.0f) {
		Re.coefficient = line.Dot(point - line_start) / length;
	}

	Re.hit_point = line_start + (line * Re.coefficient);
	Re.length = (Re.hit_point - point).Len();

	return Re;
};

//�_�Ɛ����̍ŒZ����   ���I�ȍ��͎n�_�ƏI�_�̓��[���h���W�œ����
POINT_LINE_SHORT Collision3D::PointLineSegShortLength(Vector3D line_start, Vector3D line_end, Vector3D point) {
	Vector3D end = line_end - line_start;
	POINT_LINE_SHORT Re = Collision3D::PointLineShortLength(line_start, line_end, point);

	if (!Math::CheckAcuteAngle(point, line_start, line_end)) {
		//�n�_��
		Re.hit_point = line_start;
		Re.length = (line_start - point).Len();
	}
	else if (!Math::CheckAcuteAngle(point, line_start + end, line_start)) {
		//�I�_��
		Re.hit_point = line_start + end;
		Re.length = (end - point).Len();
	}

	return Re;
}

//2�����̐����ɂȂ�ꏊ�ƃx�N�g���W��
TWOLINE_SHORT Collision3D::TwoLineShortPoint(Vector3D line_1_start, Vector3D line_1_end, Vector3D line_2_start, Vector3D line_2_end) {
	TWOLINE_SHORT Re;
	Vector3D one_way = line_1_end - line_1_start;
	Vector3D two_way = line_2_end - line_2_start;

	//���s�Ȓ��������ׂ�
	if (Math::CheckParallelRelation(line_1_start, line_1_end, line_2_start, line_2_end)) {
		POINT_LINE_SHORT pls = Collision3D::PointLineSegShortLength(line_1_start, line_1_end, line_2_start);
		Re.length = pls.length;
		Re.line_1_point = line_1_start;
		Re.line_1_coefficient = 0.0f;
		Re.line_2_point = pls.hit_point;
		Re.line_2_coefficient = pls.coefficient;

		return Re;
	}

	float Dot_OwTw = one_way.Dot(two_way);//����1�ƕ���2�̐����ȋ���
	float Dot_OsOw = one_way.Sqlen();//����1�ƕ���1�̐����ȋ���
	float Dot_TsTw = two_way.Sqlen();//����2�ƕ���2�̐����ȋ���
	Vector3D Sub_OsTs = line_1_start - line_2_start;//�n�_1����n�_2�̕���

	Re.line_1_coefficient = (Dot_OwTw * two_way.Dot(Sub_OsTs) - Dot_TsTw * one_way.Dot(Sub_OsTs)) / (Dot_OsOw * Dot_TsTw - Dot_OwTw * Dot_OwTw);
	Re.line_1_point = line_1_start + one_way * Re.line_1_coefficient;
	Re.line_2_coefficient = two_way.Dot(Re.line_1_point - line_2_start) / Dot_TsTw;
	Re.line_2_point = line_2_start + two_way * Re.line_2_coefficient;
	Re.length = (Re.line_2_point - Re.line_1_point).Len();

	return Re;
}

TWOLINE_SHORT Collision3D::TwoSegmentShortPoint(Vector3D line_1_start, Vector3D line_1_end, Vector3D line_2_start, Vector3D line_2_end) {

	TWOLINE_SHORT Re;

	Vector3D one_way = line_1_end - line_1_start;
	Vector3D two_way = line_2_end - line_2_start;

	float effective_range = 0.001f;

	//�k�ށ@���������ē_�ɂȂ��Ă���@�_�ōl����
	//����1���k�ނ��Ă��邩
	if (one_way.Sqlen() < effective_range) {
		//����1���k�ނ��Ă���
		//����2���k�ނ��Ă��邩
		if (two_way.Sqlen() < effective_range) {
			// ����2�͏k�ނ��Ă���
			Re.line_1_point = line_1_start;
			Re.line_2_point = line_2_start;
			Re.line_1_coefficient = 0.0f;
			Re.line_2_coefficient = 0.0f;
			Re.length = (line_2_start- line_1_start).Len();
			return Re;
		}
		else {
			// ����2�͏k�ނ��Ă��Ȃ�����
			//����1�̎n�_�ƒ���2�̍ŒZ����
			POINT_LINE_SHORT value = Collision3D::PointLineSegShortLength(line_2_start, line_2_end, line_1_start);
			Re.line_1_point = line_1_start;
			Re.line_1_coefficient = 0.0f;
			Re.line_2_point = value.hit_point;
			Re.line_2_coefficient = value.coefficient;
			Re.length = value.length;
			Re.line_2_coefficient = Math::Clamp(0, 1.0f, Re.line_2_coefficient);
			return Re;
		}
	}
	//����2���k�ނ��Ă��邩
	else if (two_way.Sqlen() < effective_range) {
		// ����2�͏k�ނ��Ă���
		//��Ő���1�͊m�F�����̂ł����͂��Ȃ�
		POINT_LINE_SHORT value = Collision3D::PointLineSegShortLength(line_1_start, line_1_end, line_2_start);
		Re.line_1_point = value.hit_point;
		Re.line_1_coefficient = value.coefficient;
		Re.line_2_point = line_2_start;
		Re.line_2_coefficient = 0.0f;
		Re.length = value.length;
		Re.line_1_coefficient = Math::Clamp(0, 1.0f, Re.line_1_coefficient);
		return Re;
	}

	//�k�ނ��Ȃ������̂Ő������m�ōl����
	//����1�Ɛ���2�����s��
	if (Math::CheckParallelRelation(line_1_start, line_1_end, line_2_start, line_2_end)) {
		//���s�������̂Ő����̒[�̈���o1�Ƃ���
		POINT_LINE_SHORT value = Collision3D::PointLineSegShortLength(line_1_start, line_1_end, line_2_start);
		Re.line_1_point = line_1_start;
		Re.line_1_coefficient = 0.0f;
		Re.line_2_point = value.hit_point;
		Re.line_2_coefficient = value.coefficient;
		Re.length = value.length;
		if (0.0f <= Re.line_2_coefficient && Re.line_2_coefficient <= 1.0f) {
			return Re;
		}
	}
	else {
		//���s�łȂ������̂Ő�����̍ŒZ���������߂�
		Re = Collision3D::TwoLineShortPoint(line_1_start, line_1_end, line_2_start, line_2_end);
		if (0.0f <= Re.line_1_coefficient && Re.line_1_coefficient <= 1.0f &&
			0.0f <= Re.line_2_coefficient && Re.line_2_coefficient <= 1.0f) {
			return Re;
		}
	}

	//�����̒[�������̊O���ɂ���̂�
	//����1���̃x�N�g���W����0����1�̊ԂɃN�����v���Đ������~�낷

	Re.line_1_coefficient = Math::Clamp(0, 1, Re.line_1_coefficient);
	Re.line_1_point = line_1_start + one_way * Re.line_1_coefficient;
	POINT_LINE_SHORT value = Collision3D::PointLineSegShortLength(line_2_start, line_2_end, Re.line_1_point);
	Re.line_2_coefficient = value.coefficient;
	Re.line_2_point = value.hit_point;
	Re.length = value.length;

	if (0.0f <= Re.line_2_coefficient && Re.line_2_coefficient <= 1.0f) {
		return Re;
	}
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	Re.line_2_coefficient = Math::Clamp(0, 1, Re.line_2_coefficient);
	Re.line_2_point = line_2_start + two_way * Re.line_2_coefficient;
	value = Collision3D::PointLineSegShortLength(line_1_start, line_1_end, Re.line_2_point);

	Re.line_1_coefficient = value.coefficient;
	Re.line_1_point = value.hit_point;
	Re.length = value.length;

	if (0.0f <= Re.line_1_coefficient && Re.line_1_coefficient <= 1.0f) {
		return Re;
	}
	//------------------------------------------------------------------------------------------------------------------------------------------------------
	Re.line_1_coefficient = Math::Clamp(0, 1, Re.line_1_coefficient);
	Re.line_1_point = line_1_start + one_way * Re.line_1_coefficient;
	Re.length = (Re.line_2_point - Re.line_1_point).Len();
	return Re;
}

bool Collision3D::SphereCol(Vector3D pos1, float r1, Vector3D pos2, float r2) {
	return (pos2 - pos1).Sqlen() <= (r1 + r2) * (r1 + r2);
}

bool Collision3D::SphereCol(const Sphere& sphere1, const Sphere& sphere2)
{
	return Collision3D::SphereCol(sphere1.centerPos, sphere1.r, sphere2.centerPos, sphere2.r);
}

bool Collision3D::TwoCapsuleCol(Vector3D line_1_start, Vector3D line_1_end, float r_1, Vector3D line_2_start, Vector3D line_2_end, float r_2) {
	TWOLINE_SHORT value = Collision3D::TwoSegmentShortPoint(line_1_start, line_1_end, line_2_start, line_2_end);
	return Collision3D::SphereCol(value.line_1_point, r_1, value.line_2_point, r_2);
}

bool Collision3D::TwoCapsuleCol(const Capsule& capsule1, const Capsule& capsule2)
{
	return Collision3D::TwoCapsuleCol(capsule1.down_pos.toVECTOR(), capsule1.up_pos.toVECTOR(), capsule1.r, capsule2.down_pos.toVECTOR(), capsule2.up_pos.toVECTOR(), capsule2.r);
}

bool Collision3D::SphereCapsuleCol(Vector3D spherePos, float sphereR, Vector3D capsuleStartPos, Vector3D capsuleEndPos, float capsuleR, Vector3D* shortestPos)
{
	POINT_LINE_SHORT value = Collision3D::PointLineSegShortLength(capsuleStartPos, capsuleEndPos, spherePos);
	if (shortestPos != nullptr) {
		*shortestPos = value.hit_point;
	}
	return Collision3D::SphereCol(spherePos, sphereR, value.hit_point, capsuleR);
}

bool Collision3D::SphereCapsuleCol(const Sphere& sphere, const Capsule& capsule, Vector3D* shortestPos)
{
	return Collision3D::SphereCapsuleCol(sphere.centerPos, sphere.r, capsule.down_pos, capsule.up_pos, capsule.r, shortestPos);
}

Vector3D Collision3D::PointOBB(Vector3D point, OBB obb) {
	Vector3D pos = obb.pos;
	Vector3D cp = point - pos;
	Vector3D Re = pos;
	float length = 0.0f;
	for (int i = 0; i < 3; i++) {
		length = cp.Dot(obb.dir_vec[i]);

		if (length > (obb.length[i] / 2)) {
			length = obb.length[i] / 2;
		}
		else if (length < -obb.length[i] / 2) {
			length = -obb.length[i] / 2;
		}
		Re = Re+obb.dir_vec[i]* length;
	}
	return Re;
}

bool Collision3D::OBBSphereCol(OBB obb, Vector3D point, float r, Vector3D* hitPos) {
	Vector3D pos = Collision3D::PointOBB(point, obb);

	Vector3D vector = pos - point;

	if (vector.Dot(vector) <= r * r) {
		if (hitPos != nullptr) {
			*hitPos = pos;
		}
		return true;
	}

	return false;
}

bool Collision3D::OBBSphereCol(const OBB& obb, const Sphere& sphere, Vector3D* hitPos)
{
	return Collision3D::OBBSphereCol(obb, sphere.centerPos, sphere.r, hitPos);
}

bool Collision3D::OBBCapsuleCol(OBB obb, Vector3D line_start, Vector3D line_end, float r, Vector3D* hitPos) {
	POINT_LINE_SHORT  a = Collision3D::PointLineSegShortLength(line_start, line_end, obb.pos);

	Vector3D pos = Collision3D::PointOBB(a.hit_point, obb);

	Vector3D vector = pos - a.hit_point;

	if (vector.Dot(vector) <= r * r) {
		if (hitPos != nullptr) {
			*hitPos = pos;
		}
		return true;
	}

	return false;
}

bool Collision3D::OBBCapsuleCol(OBB obb, Capsule capsule, Vector3D* hitPos) {
	return OBBCapsuleCol(obb, capsule.down_pos, capsule.up_pos, capsule.r, hitPos);
}