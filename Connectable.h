#ifndef _CONNECTABLE_H_
#define _CONNECTABLE_H_
#include "IGobject.h"
//class IGobject;
#define MAXIMUM_NUMBER_OF_CONNECTIONS (100)

typedef unsigned int ConID;



class IConnectable
{
public:
	unsigned ConnectionID;
	IGobject* connection;
	bool _initialized;
	IConnectable* Connectables[MAXIMUM_NUMBER_OF_CONNECTIONS];
	unsigned ConnectTo(IConnectable*);
	unsigned ConIDs[MAXIMUM_NUMBER_OF_CONNECTIONS];
	bool Not_hasInitialized(void);
	int current;
	int NumberOfConnectedObjects;

public:

	void SetConnection(IGobject* gobject)
	{
		connection=gobject;
		ConnectionID=0;
	}
	void SetConnection(IConnectable* connectable)
	{
		ConnectionID = ++connectable->current;
	}

	IGobject* Connection(void);


	IConnectable* getConnectables(int index);
	void setConnectables(int index,IConnectable* connectable);
	int GetNumberOfConnected(void);
	IConnectable(void)
	{
		_initialized=false;
		Not_hasInitialized();
		NumberOfConnectedObjects=0;
		current= -1;
	}
	virtual ~IConnectable(void);
	template<typename T> T* GetConnected(void)
	{
		for(int i = 0; i < MAXIMUM_NUMBER_OF_CONNECTIONS ;i++)
			if(typeid(getConnectables(i)) == typeid(T*))
				return (T*)getConnectables(i);
		return NULL;
	}
	template<typename T> T* GetConnected(ConID conid)
	{
		return (T*)getConnectables(conid-1);
	}

	template<typename T> T* AddConnectable(unsigned int*id)
	{

	Not_hasInitialized();
		
	for(int i=0;i<MAXIMUM_NUMBER_OF_CONNECTIONS;i++)
		if(ConIDs[i] == 0)
		{
			IConnectable* newcon = new T();
			newcon->SetConnection(this->connection);
			newcon->ConnectionID = i+1;
			setConnectables(i,(T*)newcon);
			*id=i+1;
			return (T*)getConnectables(i);
		}
		return NULL;
	}

	ConID* ConnectConnectableInstance(IConnectable* inst)
	{
		for(int i=0;i<MAXIMUM_NUMBER_OF_CONNECTIONS;i++)
			if(inst->Connection()->conXtor->ConIDs[i]==0)
		{
			this->Connectables[i]=inst;
			inst->Connection()->conXtor->ConIDs[i]=i+1;
			this->ConIDs[i]=inst->Connection()->conXtor->ConIDs[i];
			return &this->ConIDs[i];
		}
	}

	template<typename T> T* AddConnectable(void)
	{

	Not_hasInitialized();
		
	for(int i=0;i<MAXIMUM_NUMBER_OF_CONNECTIONS;i++)
		if(ConIDs[i]==0)
		{
			IConnectable* newcon = new T();
			newcon->SetConnection(this->connection);
			newcon->ConnectionID=i+1; 
			setConnectables(i,(T*)newcon);
			return (T*)getConnectables(i);
		}
		return NULL;
	}

	template<typename T> T* AddConnectable(IGobject* gobject)
	{

	Not_hasInitialized();
		
	for(int i=0;i<MAXIMUM_NUMBER_OF_CONNECTIONS;i++)
		if(ConIDs[i]==0)
		{
			IConnectable* newcon = new T();
			newcon->SetConnection(gobject);
			newcon->ConnectionID=ConIDs[i]=i+1;
				setConnectables(i,(T*)newcon);
			return (T*)getConnectables(i);
		}
		return NULL;
	}
};

#endif