#include "choosable.hpp"
#include "find_info.hpp"
#include "info.hpp"
#include <fcppt/container/tree/object_impl.hpp>

namespace
{

sanguis::client::level const
perk_level(
	sanguis::perk_type::type,
	sanguis::client::perk::level_map const &
);

}

sanguis::client::perk::choosable_state::type
sanguis::client::perk::choosable(
	sanguis::perk_type::type const _type,
	perk::tree const &_tree,
	perk::level_map const &_levels,
	client::level const _player_level,
	client::level const _perks_chosen
)
{
	if(
		_player_level
		==
		_perks_chosen
	)
		return perk::choosable_state::level_up;

	perk::tree const &node(
		perk::find_info(
			_type,
			_tree
		)
	);

	if(
		node.value().max_level().get()
		==
		::perk_level(
			_type,
			_levels
		)
	)
		return perk::choosable_state::max_level;

	if(
		node.has_parent()
		&&
		::perk_level(
			node.parent().value().type(),
			_levels
		)
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

namespace
{

sanguis::client::level const
perk_level(
	sanguis::perk_type::type const _type,
	sanguis::client::perk::level_map const &_map
)
{
	sanguis::client::perk::level_map::const_iterator const it(
		_map.find(
			_type
		)
	);

	return
		it == _map.end()
		?
			sanguis::client::level(
				0
			)
		:
			it->second;
}

}
