#include "dxlib.h"
#include <source_location>

#define	SAFE_DELETE(x)	if(x){delete x;x=nullptr;}
#define S_Draw(y,value) DrawFormatString(0,y*15,GetColor(255,255,255),"%u",value);
#define D_Draw(y,value) DrawFormatString(0,y*15,GetColor(255,255,255),"%d",value);
#define F_Draw(y,value) DrawFormatString(0,y*15,GetColor(255,255,255),"%f",value);
#define V_Draw(y,value) DrawFormatString(0,y*15,GetColor(255,255,255),"%f;%f;%f",value.x,value.y,value.z)

// �J���[�R�[�h�萔
#define COLOR_WHITE (0xFFFFFF)
#define COLOR_RED   (0xFF0000)
#define COLOR_GREEN (0x00FF00)
#define COLOR_BLUE  (0x0000FF)
#define COLOR_BLACK (0x000000)

void DebugErrar(const std::source_location location = std::source_location::current()) {
	std::string errar = "�t�@�C����:" + std::string(location.file_name()) + "\n" + "�s:" + std::to_string(location.line()) + "�ŃG���[����";
	MessageBox(NULL, errar.c_str(), "", MB_OK);
}

// �f�o�b�O�p�G���[�\��
#define DebugErrar DebugErrar();