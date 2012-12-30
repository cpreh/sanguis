#include <sanguis/perk_type.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/perks/tree/max_level.hpp>
#include <sanguis/server/perks/tree/required_player_level.hpp>
#include <sanguis/server/perks/tree/required_parent_level.hpp>
#include <sanguis/server/perks/tree/status.hpp>
#include <fcppt/assert/pre.hpp>


sanguis::server::perks::tree::status::status(
	sanguis::perk_type const _type,
	sanguis::server::perks::tree::required_player_level const _required_player_level,
	sanguis::server::perks::tree::required_parent_level const _required_parent_level,
	sanguis::server::perks::tree::max_level const _max_level
)
:
	type_(
		_type
	),
	required_player_level_(
		_required_player_level
	),
	required_parent_level_(
		_required_parent_level
	),
	max_level_(
		_max_level
	),
	level_(
		0u
	)
{
}

void
sanguis::server::perks::tree::status::choose()
{
	FCPPT_ASSERT_PRE(
		this->type() != perk_type::size
	);

	FCPPT_ASSERT_PRE(
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

sanguis::perk_type
sanguis::server::perks::tree::status::type() const
{
	return type_;
}
