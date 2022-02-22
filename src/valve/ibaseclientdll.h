#pragma once
#include "../util/memory.h"

#include "crecvtable.h"

class CClientClass
{
public:
	void* createFn;
	void* createEventFn;
	char* networkName;
	CRecvTable* table;
	CClientClass* next;
	std::int32_t classID;
};

class IBaseClientDLL
{
public:
	constexpr CClientClass* GetAllClasses() noexcept
	{
		return memory::Call<CClientClass*>(this, 8);
	}
};
