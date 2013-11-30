#include <sanguis/perk_type.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/player_level.hpp>
#include <sanguis/client/perk/choosable.hpp>
#include <sanguis/client/perk/choosable_state.hpp>
#include <sanguis/client/perk/find_info_const.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/level.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <fcppt/assert/pre.hpp>


sanguis::client::perk::choosable_state
sanguis::client::perk::choosable(
	sanguis::perk_type const _type,
	sanguis::client::perk::tree const &_tree,
	sanguis::client::player_level const _player_level,
	sanguis::client::level const _perks_chosen
)
{
	sanguis::client::perk::tree const &node(
		sanguis::client::perk::find_info_const(
			_type,
			_tree
		)
	);

	FCPPT_ASSERT_PRE(
		node.value().has_value()
	);

	sanguis::client::perk::info const &info(
		*node.value()
	);

	FCPPT_ASSERT_PRE(
		node.has_parent()
	);

	if(
		info.max_level().get()
		==
		info.level()
	)
		return
			sanguis::client::perk::choosable_state::max_level;

	if(
		node.parent().has_value()
		&&
		node.parent()->value()->level()
		<
		info.required_parent_level().get()
	)
		return
			sanguis::client::perk::choosable_state::parent_level;

	if(
		info.required_player_level().get()
		>
		_player_level
	)
		return
			sanguis::client::perk::choosable_state::player_level;

	if(
		_player_level.get()
		==
		_perks_chosen
	)
		return
			sanguis::client::perk::choosable_state::level_up;

	return
		sanguis::client::perk::choosable_state::ok;
}
