#include <sanguis/messages/available_perks.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/enum.hpp>
#include <sanguis/messages/perk_tree_node.hpp>
#include <sanguis/messages/perk_tree_node_list.hpp>
#include <sanguis/messages/types/enum.hpp>
#include <sanguis/messages/types/enum_vector.hpp>
#include <sanguis/server/send_available_perks.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/perks/tree/object.hpp>
#include <sanguis/server/perks/tree/status.hpp>
#include <fcppt/container/tree/pre_order.hpp>


namespace
{

sanguis::messages::types::enum_vector const
make_children(
	sanguis::server::perks::tree::object const &
);

}

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

	traversal trav(
		tree
	);

	sanguis::messages::perk_tree_node_list nodes;

	for(
		auto const &element : trav
	)
	{
		sanguis::server::perks::tree::status const &info(
			element.value()
		);

		nodes.push_back(
			sanguis::messages::perk_tree_node(
				static_cast<
					sanguis::messages::types::enum_
				>(
					info.type()
				),
				info.required_player_level().get(),
				info.required_parent_level().get(),
				info.max_level().get(),
				::make_children(
					element
				)
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

namespace
{

sanguis::messages::types::enum_vector const
make_children(
	sanguis::server::perks::tree::object const &_node
)
{
	sanguis::messages::types::enum_vector ret;

	for(
		auto const element : _node
	)
		ret.push_back(
			static_cast<
				sanguis::messages::types::enum_
			>(
				element.value().type()
			)
		);

	return ret;
}

}
