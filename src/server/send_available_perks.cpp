#include "send_available_perks.hpp"
#include "entities/player.hpp"
#include "../messages/available_perks.hpp"
#include "../messages/create.hpp"
#include "../messages/enum.hpp"
#include "../messages/perk_tree_node.hpp"
#include "../messages/perk_tree_node_list.hpp"
#include "../messages/types/enum_vector.hpp"
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/container/tree/pre_order.hpp>
#include <fcppt/container/tree/object_impl.hpp>

namespace
{

sanguis::messages::types::enum_vector const
make_children(
	sanguis::server::perks::tree::object const &
);

}

void
sanguis::server::send_available_perks(
	entities::player const &_player,
	server::unicast_callback const &_send
)
{
	perks::tree::object const &tree(
		_player.perk_tree()
	);

	typedef 
	fcppt::container::tree::pre_order<
		perks::tree::object const
	> traversal;
	
	traversal trav(
		tree
	);

	messages::perk_tree_node_list nodes;

	for(
		traversal::iterator it(
			trav.begin()
		);
		it != trav.end();
		++it
	)
		nodes.push_back(
			messages::perk_tree_node(
				static_cast<
					messages::types::enum_
				>(
					it->value().type()
				),
				::make_children(
					*it
				)
			)
		);

	_send(
		_player.player_id(),
		messages::create(
			messages::available_perks(
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
		sanguis::server::perks::tree::object::const_iterator it(
			_node.begin()
		);
		it != _node.end();
		++it
	)
		ret.push_back(
			static_cast<
				sanguis::messages::types::enum_
			>(
				it->value().type()
			)
		);

	return ret;
}

}
