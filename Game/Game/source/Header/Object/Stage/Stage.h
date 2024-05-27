#include "../Base/ObjectBase.h"
class Stage : public ObjectBase
{
public:
	Stage(std::string name);
	~Stage();
	virtual bool Init()override;
	virtual bool Update()override;
};