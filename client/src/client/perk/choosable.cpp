#include <sanguis/perk_type.hpp>
#include <sanguis/client/player_level.hpp>
#include <sanguis/client/perk/choosable.hpp>
#include <sanguis/client/perk/choosable_state.hpp>
#include <sanguis/client/perk/find_info_const.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/remaining_levels.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <fcppt/const.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/assert/optional_error.hpp>


sanguis::client::perk::choosable_state
sanguis::client::perk::choosable(
	sanguis::perk_type const _type,
	sanguis::client::perk::tree const &_tree,
	sanguis::client::player_level const _player_level,
	sanguis::client::perk::remaining_levels const _remaining_levels
)
{
	sanguis::client::perk::tree const &node(
		sanguis::client::perk::find_info_const(
			_type,
			_tree
		)
	);

	sanguis::client::perk::info const &info(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			node.value()
		)
	);

	sanguis::client::perk::tree const &parent_node(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			node.parent()
		)
	);

	if(
		info.max_level().get()
		==
		info.level()
	)
		return
			sanguis::client::perk::choosable_state::max_level;

	if(
		fcppt::maybe(
			parent_node.value(),
			fcppt::const_(
				false
			),
			[
				&info
			](
				sanguis::client::perk::info const &_parent_info
			)
			{
				return
					_parent_info.level()
					<
					info.required_parent_level().get();
			}
		)
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
		_remaining_levels.get().get()
		==
		0u
	)
		return
			sanguis::client::perk::choosable_state::level_up;

	return
		sanguis::client::perk::choosable_state::ok;
}
