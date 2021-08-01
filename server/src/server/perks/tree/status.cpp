#include <sanguis/perk_type.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/perks/tree/max_level.hpp>
#include <sanguis/server/perks/tree/required_parent_level.hpp>
#include <sanguis/server/perks/tree/required_player_level.hpp>
#include <sanguis/server/perks/tree/status.hpp>


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
		0U
	)
{
}

void
sanguis::server::perks::tree::status::choose()
{
	if(
		level_.get()
		==
		max_level_.get()
	)
	{
		return;
	}

	++level_;
}

sanguis::server::perks::tree::required_player_level
sanguis::server::perks::tree::status::required_player_level() const
{
	return
		required_player_level_;
}

sanguis::server::perks::tree::required_parent_level
sanguis::server::perks::tree::status::required_parent_level() const
{
	return
		required_parent_level_;
}

sanguis::server::perks::tree::max_level
sanguis::server::perks::tree::status::max_level() const
{
	return
		max_level_;
}

sanguis::server::level
sanguis::server::perks::tree::status::level() const
{
	return
		level_;
}

sanguis::perk_type
sanguis::server::perks::tree::status::type() const
{
	return
		type_;
}
