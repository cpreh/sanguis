#include "status.hpp"
#include <fcppt/assert.hpp>
#include <limits>

sanguis::server::perks::tree::status::status()
:
	type_(perk_type::size),
	required_player_level_(0),
	required_parent_level_(0),
	max_level_(0),
	level_(
		std::numeric_limits<
			server::level::value_type
		>::max()
	)
{
}

sanguis::server::perks::tree::status::status(
	perk_type::type const _type,
	tree::required_player_level const _required_player_level,
	tree::required_parent_level const _required_parent_level,
	tree::max_level const _max_level
)
:
	type_(_type),
	required_player_level_(_required_player_level),
	required_parent_level_(_required_parent_level),
	max_level_(_max_level),
	level_(0)
{
}
	
void
sanguis::server::perks::tree::status::choose()
{
	FCPPT_ASSERT(
		this->type() != perk_type::size
	);

	FCPPT_ASSERT(
		level_.get() < max_level_.get()
	);

	++level_;
}

sanguis::server::perks::tree::required_player_level const
sanguis::server::perks::tree::status::required_player_level() const
{
	return required_player_level_;
}

sanguis::server::perks::tree::required_parent_level const
sanguis::server::perks::tree::status::required_parent_level() const
{
	return required_parent_level_;
}

sanguis::server::perks::tree::max_level const
sanguis::server::perks::tree::status::max_level() const
{
	return max_level_;
}

sanguis::server::level const
sanguis::server::perks::tree::status::level() const
{
	return level_;
}

sanguis::perk_type::type
sanguis::server::perks::tree::status::type() const
{
	return type_;
}
