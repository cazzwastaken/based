#pragma once
#include "../util/memory.h"

class CEntity;
class ITraceFilter
{
public:
	enum ETraceType : std::int32_t
	{
		TRACE_EVERYTHING = 0,
		TRACE_WORLD_ONLY,
		TRACE_ENTITIES_ONLY,
		TRACE_EVERYTHING_FILTER_PROPS
	};

	virtual bool ShouldHitEntity(CEntity* entity, std::int32_t contentsMask) = 0;
	virtual std::int32_t GetTraceType() const = 0;
};

class CTraceFilter : public ITraceFilter
{
public:
	CTraceFilter(CEntity* entity) noexcept : skipEntity(entity) { }

	bool ShouldHitEntity(CEntity* entity, std::int32_t contentsMask) override
	{
		return entity != this->skipEntity;
	}

	std::int32_t GetTraceType() const override
	{
		return TRACE_EVERYTHING;
	}

private:
	const CEntity* skipEntity;
};

class CRay
{
public:

};

class CTrace
{
public:

};

// interface itself
class IEngineTrace
{
public:

};
