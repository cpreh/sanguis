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
	entities::base &owner_
)
{
	if(
		!can_raise_level()
	)
		throw exception(
			FCPPT_TEXT("Can't raise perk level!")
		);
	
	change(
		owner_,
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
	perk_type::type const type_
)
:
	type_(type_),
	level_(0)
{}

sanguis::server::perks::level_type
sanguis::server::perks::perk::level() const
{
	return level_;
}
