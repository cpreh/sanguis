#include <sanguis/perk_type.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <sanguis/server/perks/perk.hpp>


void
sanguis::server::perks::perk::update(
	sanguis::server::entities::base &,
	sanguis::server::environment::object &
)
{
}

void
sanguis::server::perks::perk::raise_level(
	sanguis::server::entities::base &_owner
)
{
	this->change(
		_owner,
		sanguis::server::perks::level_diff(
			1
		)
	);

	++level_;
}

sanguis::perk_type
sanguis::server::perks::perk::type() const
{
	return type_;
}

sanguis::server::perks::perk::~perk()
{
}

sanguis::server::perks::perk::perk(
	sanguis::perk_type const _type
)
:
	type_(
		_type
	),
	level_(
		0u
	)
{
}

sanguis::server::level const
sanguis::server::perks::perk::level() const
{
	return level_;
}
