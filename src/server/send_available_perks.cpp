#include <sanguis/optional_perk_type.hpp>
#include <sanguis/messages/available_perks.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/perk_tree_node.hpp>
#include <sanguis/messages/perk_tree_node_list.hpp>
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

	sanguis::messages::perk_tree_node_list nodes;

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
			sanguis::messages::perk_tree_node(
				info->type(),
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
		*sanguis::messages::create(
			sanguis::messages::available_perks(
				_player.id(),
				nodes
			)
		)
	);
}
