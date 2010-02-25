#include "status.hpp"
#include <fcppt/assert.hpp>
#include <limits>

sanguis::server::perks::status::status()
:
	type_(perk_type::size),
	required_player_level_(0),
	required_parent_level_(0),
	level_(
		std::numeric_limits<
			level_type
		>::max()
	)
{}

sanguis::server::perks::status::status(
	perk_type::type const type_,
	level_type const required_player_level_,
	level_type const required_parent_level_
)
:
	type_(type_),
	required_player_level_(required_player_level_),
	required_parent_level_(required_parent_level_),
	level_(0)
{}
	
void
sanguis::server::perks::status::choose()
{
	FCPPT_ASSERT(type() != perk_type::size);
	++level_;
}

sanguis::server::perks::level_type
sanguis::server::perks::status::required_player_level() const
{
	return required_player_level_;
}

sanguis::server::perks::level_type
sanguis::server::perks::status::required_parent_level() const
{
	return required_parent_level_;
}
sanguis::server::perks::level_type
sanguis::server::perks::status::level() const
{
	return level_;
}

sanguis::perk_type::type
sanguis::server::perks::status::type() const
{
	return type_;
}
