#include "Connectable.h"







bool
IConnectable::Not_hasInitialized(void)
{
	if(!this->_initialized)
	{
		for(int i=0; i < MAXIMUM_NUMBER_OF_CONNECTIONS ; i++)
		{	this->ConIDs[i] = 0; this->Connectables[i]=NULL;}
		this->NumberOfConnectedObjects = 0;
		this->current = -1;

		this->_initialized=true;
		return this->_initialized;
	}
	return false;
}








IConnectable::~IConnectable(void)
{
	for(int i = 0; i < MAXIMUM_NUMBER_OF_CONNECTIONS ;i++)
		delete this->Connectables[i];
}



IGobject* 
IConnectable::Connection(void)
{
	return this->connection;
}
//template<typename T> T*
//IConnectable::GetConnected(void)
//{
//	for(int i = 0; i < MAXIMUM_NUMBER_OF_CONNECTIONS ;i++)
//		if(Connectables[i] == class:IConnectable)
//			return (T*)_Connectables[i];
//}



IConnectable*
IConnectable::getConnectables(int index)
{
	return this->Connectables[index];
}

void
IConnectable::setConnectables(int index,IConnectable* connectable)
{
	this->Connectables[index]=connectable;
	this->ConIDs[index]=connectable->ConnectionID;
}
//template<typename T> T*
//IConnectable::GetConnected(ConID conid)
//{
//	return (T*)_Connectables[conid];
//}

//template<typename T> T*
//IConnectable::AddConnection(int &id)
//	{
//	for(int i=0;i<MAXIMUM_NUMBER_OF_CONNECTIONS;i++)
//		if(GobIDs[i]==0)
//		{
//			Connectables[i] = new T();
//			id=i;
//			return (T*)_Connectables[i];
//		}
//		return NULL;
//	}

int
IConnectable::GetNumberOfConnected(void)
{
	return this->NumberOfConnectedObjects;
}