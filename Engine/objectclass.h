#ifndef _OBJECTCLASS_H_
#define _OBJECTCLASS_H_

#include "modelclass.h"

class ObjectClass
{
public:
	ObjectClass();
	ObjectClass(const ObjectClass&);
	~ObjectClass();


private:
	ModelClass* m_Model;
};
#endif // !_OBJECTCLASS_
