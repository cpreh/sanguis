#include "perk.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>

sanguis::server::perks::perk::perk()
:
	level_(1)
{}

void sanguis::server::perks::perk::raise_level()
{
	if(!can_raise_level())
		throw exception(
			SGE_TEXT("Can't raise perk level!"));
	++level_;
}

sanguis::server::perks::perk::~perk()
{}

sanguis::server::perks::perk::level_type
sanguis::server::perks::perk::level() const
{
	return level_;
}

void sanguis::server::perks::perk::apply(
	entities::entity &e)
{
	do_apply(e);
}
