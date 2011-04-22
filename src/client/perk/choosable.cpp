#include "choosable.hpp"
#include "find_info.hpp"
#include "info.hpp"
#include <fcppt/container/tree/object_impl.hpp>

sanguis::client::perk::choosable_state::type
sanguis::client::perk::choosable(
	sanguis::perk_type::type const _type,
	perk::tree const &_tree,
	perk::level_map &_levels,
	client::level const _player_level
)
{
	perk::tree const &node(
		perk::find_info(
			_type,
			_tree
		)
	);

	if(
		node.value().max_level().get()
		==
		_levels[
			_type
		]
	)
		return perk::choosable_state::max_level;

	if(
		node.has_parent()
		&&
		_levels[
			node.parent().value().type()
		]
		<
		node.value().required_parent_level().get()
	)
		return perk::choosable_state::parent_level;
	
	if(
		node.value().required_player_level().get()
		> _player_level
	)
		return perk::choosable_state::player_level;
	
	return perk::choosable_state::ok;
}
