#include "../../Header/Function/mymath.h"
 //degree��radian
float Math::DegToRad(float deg) {
	return deg * PI / 180.0f;		// �p�x��degree����radian�ɕϊ�
}

// radian��degree
float Math::RadToDeg(float rad) {
	return rad * 180.0f / PI;		// �p�x��radian����degree�ɕϊ�
}

// �N�����v
float Math::Max(float left, float right) {
	return left > right ? left : right;
};

float Math::Min(float left, float right) {
	return left < right ? left : right;
};

float Math::Clamp(float min_n, float max_n, float n) {
	if (n <= min_n) { return min_n; }
	if (n >= max_n) { return max_n; }
	return n;
}

//�}�g���N�X�����x�N�g���𐳋K�����ēn��
//���[�v���Ŏg���₷��
Vector3D  Math::NormRotMatrix(Vector3D norm, float rotation, int type) {
	MATRIX conv_matrix = MGetIdent();
	Vector3D re_vec;
	switch (type) {
	case 0://x
		conv_matrix = MGetRotX(rotation);
		break;
	case 1://y
		conv_matrix = MGetRotY(rotation);
		break;
	case 2://z
		conv_matrix = MGetRotZ(rotation);
		break;
	default:
		return VGet(-1,0,0);
	}
	re_vec = VTransform(norm.toVECTOR(), conv_matrix);

	return re_vec.Normalize();
}

//�����x�N�g�����~�������Ɏg���܂��B
Vector3D Math::MatrixToVector(MATRIX matrix,int index) {
	return VGet(matrix.m[index][0], matrix.m[index][1], matrix.m[index][2]);
}

// �������ɓ��e���ꂽ���������瓊�e���������Z�o
float  Math::LenSegOnSeparateAxis(Vector3D Sep, Vector3D e1, Vector3D e2, Vector3D e3 ) {

	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	// ������Sep�͕W��������Ă��邱��
	float r1 = fabs(Sep.Dot(e1));
	float r2 = fabs(Sep.Dot(e2));
	float r3 = 0.0f;
	if (e3.x != 0 || e3.y != 0 || e3.z != 0) {
		r3 = fabs(Sep.Dot(e3));
	}
	return r1 + r2 + r3;
}

MATRIX Math::MMultXYZ(float dir_x, float dir_y, float dir_z) {
	MATRIX matrix;
	matrix = MGetRotX(dir_x);
	matrix = MMult(matrix, MGetRotY(dir_y));
	matrix = MMult(matrix, MGetRotZ(dir_z));

	return matrix;
};

MATRIX Math::MMultXYZToMatrix(float dir_x, float dir_y, float dir_z) {
	MATRIX matrix;
	matrix = MGetRotX(dir_x);
	matrix = MMult(matrix, MGetRotY(dir_y));
	matrix = MMult(matrix, MGetRotZ(dir_z));
	matrix = MMult(matrix, GetCameraBillboardMatrix());

	return matrix;
};

bool Math::SetMatrixToVector(Vector3D& vec_x, Vector3D& vec_y, Vector3D& vec_z, const MATRIX matrix) {
	vec_x = Vector3D(matrix.m[0][0], matrix.m[0][1], matrix.m[0][2]);
	vec_y = Vector3D(matrix.m[1][0], matrix.m[1][1], matrix.m[1][2]);
	vec_z = Vector3D(matrix.m[2][0], matrix.m[2][1], matrix.m[2][2]);
	return true;
}

// �s�p���ǂ���
bool Math::CheckAcuteAngle(Vector3D p1, Vector3D p2, Vector3D p3) {
	return (p1 - p2).Dot(p3 - p2) >= 0.0f;
}

// ���s���ǂ���
bool Math::CheckParallelRelation(Vector3D line_1_start, Vector3D line_1_end, Vector3D line_2_start, Vector3D line_2_end) {
	Vector3D line_1 = line_1_end - line_1_start;
	Vector3D line_2 = line_2_end - line_2_start;
	float value = line_1.Cross(line_2).Len();
	float effective_range = 0.001f;
	return -effective_range <= value && value <= effective_range;
}

// �������ǂ���
bool Math::CheckVerticalRelation(Vector3D line_1_start, Vector3D line_1_end, Vector3D line_2_start, Vector3D line_2_end) {
	Vector3D line_1 = line_1_end - line_1_start;
	Vector3D line_2 = line_2_end - line_2_start;
	float dot = line_1.Dot(line_2);
	float effective_range = 0.001f;
	return -effective_range <= dot && dot <= effective_range;
}

// 2�̃x�N�g���̂Ȃ��p���v�Z����
// �߂�l: �p�x(radian) 
float Math::CalcVectorAngle(Vector3D v1, Vector3D v2)
{
	float v1SquareSize = v1.Sqlen();
	float v2SquareSize = v2.Sqlen();
	if (v1SquareSize > 0.000000f && v2SquareSize > 0.000000f) {
		float cos = v1.Dot(v2) / (sqrt(v1SquareSize) * sqrt(v2SquareSize));
		return acos(cos);
	}
	return 0;
}

// 3D���f��������vForward�̕��������ʂɂȂ�悤�ɉ�]������
void Math::SetModelForward_RotationY(int modelHandle, Vector3D vForwad)
{
	Vector3D vBase = Vector3D(0.0f, 0.0f, -1.0f);
	vForwad.y = 0.0f;
	float angle = CalcVectorAngle(vBase, vForwad);
	angle *= vForwad.x < 0.0f ? 1.0f : -1.0f;
	MV1SetRotationXYZ(modelHandle, VGet(0, angle, 0));
}
