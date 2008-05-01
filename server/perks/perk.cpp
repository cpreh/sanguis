#include "perk.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>

sanguis::server::perks::perk::perk()
: entity_(0),
  level_(0)
{}

void sanguis::server::perks::perk::bind(entity &e)
{
	entity_ = &e;
}

void sanguis::server::perks::perk::raise_level()
{
	if(!can_raise_level())
		throw sge::exception(
			SGE_TEXT("Can't raise perk level!"));
	deactivate();
	++level_;
	activate();
}

sanguis::server::perks::perk::~perk()
{}

sanguis::server::perks::perk::level_type
sanguis::server::perks::perk::level() const
{
	return level_;
}

sanguis::server::entity &
sanguis::server::perks::perk::get_entity() const
{
	if(!entity_)
		throw sge::exception(
			SGE_TEXT("perk has no entity!"));
	return *entity_;
}
