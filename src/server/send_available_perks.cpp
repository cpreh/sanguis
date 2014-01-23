#include <sanguis/optional_perk_type.hpp>
#include <sanguis/messages/server/available_perks.hpp>
#include <sanguis/messages/server/create.hpp>
#include <sanguis/messages/server/types/perk_tree_node.hpp>
#include <sanguis/messages/server/types/perk_tree_node_vector.hpp>
#include <sanguis/server/send_available_perks.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/perks/tree/object.hpp>
#include <sanguis/server/perks/tree/optional_status.hpp>
#include <fcppt/container/tree/pre_order.hpp>


void
sanguis::server::send_available_perks(
	sanguis::server::entities::player const &_player,
	sanguis::server::unicast_callback const &_send
)
{
	sanguis::server::perks::tree::object const &tree(
		_player.perk_tree()
	);

	typedef
	fcppt::container::tree::pre_order<
		sanguis::server::perks::tree::object const
	> traversal;

	sanguis::messages::server::types::perk_tree_node_vector nodes;

	for(
		auto const &element
		:
		traversal(
			tree
		)
	)
	{
		sanguis::server::perks::tree::optional_status const &info(
			element.value()
		);

		if(
			!info.has_value()
		)
			continue;

		nodes.push_back(
			sanguis::messages::server::types::perk_tree_node(
				info->type(),
				info->level().get(),
				info->required_player_level().get(),
				info->required_parent_level().get(),
				info->max_level().get(),
				element.parent()->value().has_value()
				?
					sanguis::optional_perk_type(
						element.parent()->value()->type()
					)
				:
					sanguis::optional_perk_type()
			)
		);
	}

	_send(
		_player.player_id(),
		*sanguis::messages::server::create(
			sanguis::messages::server::available_perks(
				nodes,
				_player.skill_points().get()
			)
		)
	);
}
