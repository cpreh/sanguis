#include "perk.hpp"

void
sanguis::server::perks::perk::update(
	entities::base &,
	sanguis::time_delta const &,
	environment::object &
)
{
}

void
sanguis::server::perks::perk::raise_level(
	entities::base &_owner
)
{
	this->change(
		_owner,
		perks::level_diff(
			1
		)
	);

	++level_;
}

sanguis::perk_type::type
sanguis::server::perks::perk::type() const
{
	return type_;
}

sanguis::server::perks::perk::~perk()
{
}

sanguis::server::perks::perk::perk(
	perk_type::type const _type
)
:
	type_(_type),
	level_(0)
{
}

sanguis::server::level const
sanguis::server::perks::perk::level() const
{
	return level_;
}
