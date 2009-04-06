#include "perk.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>

void sanguis::server::perks::perk::raise_level()
{
	if(!can_raise_level())
		throw exception(
			SGE_TEXT("Can't raise perk level!"));
	++level_;
}

sanguis::perk_type::type
sanguis::server::perks::perk::type() const
{
	return type_;
}

sanguis::server::perks::perk::~perk()
{}

sanguis::server::perks::perk::perk(
	perk_type::type const type_)
:
	type_(type_),
	level_(1)
{}

sanguis::server::perks::perk::level_type
sanguis::server::perks::perk::level() const
{
	return level_;
}

void sanguis::server::perks::perk::apply(
	entities::entity &e,
	time_type const time,
	environment const &env)
{
	do_apply(
		e,
		time,
		env
	);
}
