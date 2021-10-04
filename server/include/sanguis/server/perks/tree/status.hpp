#ifndef SANGUIS_SERVER_PERKS_TREE_STATUS_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_TREE_STATUS_HPP_INCLUDED

#include <sanguis/perk_type.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/perks/tree/max_level.hpp>
#include <sanguis/server/perks/tree/required_parent_level.hpp>
#include <sanguis/server/perks/tree/required_player_level.hpp>
#include <sanguis/server/perks/tree/status_fwd.hpp>


namespace sanguis::server::perks::tree
{

class status
{
public:
	status(
		sanguis::perk_type,
		sanguis::server::perks::tree::required_player_level,
		sanguis::server::perks::tree::required_parent_level,
		sanguis::server::perks::tree::max_level
	);

	void
	choose();

	[[nodiscard]]
	sanguis::server::perks::tree::required_player_level
	required_player_level() const;

	[[nodiscard]]
	sanguis::server::perks::tree::required_parent_level
	required_parent_level() const;

	[[nodiscard]]
	sanguis::server::perks::tree::max_level
	max_level() const;

	[[nodiscard]]
	sanguis::server::level
	level() const;

	[[nodiscard]]
	sanguis::perk_type
	type() const;
private:
	sanguis::perk_type type_;

	sanguis::server::perks::tree::required_player_level required_player_level_;

	sanguis::server::perks::tree::required_parent_level required_parent_level_;

	sanguis::server::perks::tree::max_level max_level_;

	sanguis::server::level level_;
};

}

#endif
