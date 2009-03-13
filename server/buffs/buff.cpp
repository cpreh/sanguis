#include "buff.hpp"
#include <typeinfo>

bool
sanguis::server::buffs::buff::stacks(
	buff const &b) const
{
	// default:
	// same buffs from the same source do not stack
	return b.source() != source()
		|| typeid(*this) != typeid(b);
}

bool
sanguis::server::buffs::buff::expired() const
{
	return expired_;
}

sanguis::entity_id
sanguis::server::buffs::buff::source() const
{
	return source_;
}

sanguis::server::buffs::buff::~buff()
{}

sanguis::server::buffs::buff::buff(
	entity_id const source_)
:
	source_(source_),
	expired_(false)
{}

void
sanguis::server::buffs::buff::expire()
{
	expired_ = true;
}
