#include <sanguis/client/perk/choosable.hpp>
#include <sanguis/client/perk/find_info.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/level.hpp>
#include <sanguis/client/perk/level_map.hpp>
#include <sanguis/perk_type.hpp>
#include <fcppt/container/tree/object_impl.hpp>

namespace
{

sanguis::client::perk::level const
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
	client::player_level const _player_level,
	client::level const _perks_chosen
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

	if(
		_player_level.get()
		==
		_perks_chosen
	)
		return perk::choosable_state::level_up;

	return perk::choosable_state::ok;
}

namespace
{

sanguis::client::perk::level const
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
			sanguis::client::perk::level(
				0
			)
		:
			it->second;
}

}
