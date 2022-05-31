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
	constexpr CRay(const CVector& start, const CVector& end) noexcept :
		start(start), delta(end - start)
	{
		isSwept = delta.x || delta.y || delta.z;
	}

	CVector start;
	float pad0{ };
	CVector delta;
	float pad1{ };
	CVector startOffset{ };
	float pad2{ };
	CVector extents{ };
	float pad3{ };
	const CMatrix3x4* worldAxisTransform{ nullptr };
	bool isRay{ true };
	bool isSwept;
};

class CPlane
{
public:
	CVector normal;
	float distance;
	std::byte type;
	std::byte signBits;
	std::byte pad[2];
};

class CSurface 
{
public:
	const char* name;
	short surfaceProps;
	std::uint16_t flags;
};

class CTrace
{
public:
	CVector startPos;
	CVector endPos;
	CPlane plane;

	float fraction;

	int contents;
	std::uint16_t dispFlags;

	bool allSolid;
	bool startSolid;

	float fractionLeftSolid;
	CSurface surface;

	int hitgroup;

	short physicsBone;
	std::uint16_t worldSurfaceIndex;

	CEntity* entity;
	int hitbox;
};

// interface itself
class IEngineTrace
{
public:
	constexpr void TraceRay(const CRay& ray, std::uint32_t mask, const CTraceFilter& filter, CTrace& trace) noexcept
	{
		memory::Call<void>(this, 5, std::cref(ray), mask, std::cref(filter), std::ref(trace));
	}
};
