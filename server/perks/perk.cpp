#include "perk.hpp"
#include "../../exception.hpp"
#include <fcppt/text.hpp>
#include <fcppt/assert.hpp>

void
sanguis::server::perks::perk::update(
	entities::base &,
	time_type const,
	environment::object_ptr const
)
{
}

bool
sanguis::server::perks::perk::can_raise_level() const
{
	FCPPT_ASSERT(
		level() <= max_level()
	);

	return level() < max_level();
}

void
sanguis::server::perks::perk::raise_level(
	entities::base &_owner
)
{
	if(
		!can_raise_level()
	)
		throw exception(
			FCPPT_TEXT("Can't raise perk level!")
		);
	
	change(
		_owner,
		1
	);

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
	perk_type::type const _type
)
:
	type_(_type),
	level_(0)
{}

sanguis::server::perks::level_type
sanguis::server::perks::perk::level() const
{
	return level_;
}
