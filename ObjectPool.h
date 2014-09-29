#ifndef ___OBJ_POOL___
#define ___OBJ_POOL___
#include "IGobject.h"
#define INITALAMOUNT_ON_DOUBLES 5000
#define AMOUNT_ON_GOBJECTS 200
class ObjectPool
{
private:
	ObjectPool(void);
public:
	virtual ~ObjectPool(void);

	ObjectPool* GetInstance(void);
	double* GetADouble(unsigned& ID);
	void RejectDouble(double* D,unsigned& ID);

	IGobject* GetAGobject(unsigned& ID);
	void RejectGobject(IGobject* gobj,unsigned& ID);
};


#endif