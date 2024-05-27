#include "../../../Header/Object/Base/ObjectBase.h"
ObjectBase::ObjectBase(std::string name){
	_name = name;
};

ObjectBase::~ObjectBase(){

};

bool ObjectBase::Init(){
	return true;
};

bool ObjectBase::Update(){
	return true;
};

bool ObjectBase::SetModelAndLayer(int modelHandle, int layer){
	return true;
};
