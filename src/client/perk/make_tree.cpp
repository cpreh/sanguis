#include <sanguis/perk_type.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/player_level.hpp>
#include <sanguis/client/perk/compare.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/max_level.hpp>
#include <sanguis/client/perk/make_tree.hpp>
#include <sanguis/client/perk/required_parent_level.hpp>
#include <sanguis/client/perk/required_player_level.hpp>
#include <sanguis/messages/perk_tree_node.hpp>
#include <sanguis/messages/perk_tree_node_list.hpp>
#include <sanguis/messages/roles/max_perk_level.hpp>
#include <sanguis/messages/roles/perk_children.hpp>
#include <sanguis/messages/roles/perk_label.hpp>
#include <sanguis/messages/roles/required_perk_parent_level.hpp>
#include <sanguis/messages/roles/required_perk_player_level.hpp>
#include <fcppt/cast_to_enum.hpp>
#include <fcppt/algorithm/find_if_exn.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/tree/object_impl.hpp>
#include <fcppt/container/tree/pre_order.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

sanguis::client::perk::info const
make_info(
	sanguis::messages::perk_tree_node const &
);

}

sanguis::client::perk::tree_unique_ptr
sanguis::client::perk::make_tree(
	sanguis::messages::perk_tree_node_list const &_list
)
{
	// this code highly depends on the order in which the server serializes the tree

	FCPPT_ASSERT_PRE(
		!_list.empty()
	);

	// start with the dummy head, the server will always send one
	sanguis::client::perk::tree_unique_ptr ret(
		fcppt::make_unique_ptr<
			sanguis::client::perk::tree
		>(
			::make_info(
				_list.front()
			)
		)
	);

	for(
		auto const &item : _list
	)
	{
		typedef fcppt::container::tree::pre_order<
			sanguis::client::perk::tree
		> traversal;

		traversal trav(
			*ret
		);

		traversal::iterator const pos(
			fcppt::algorithm::find_if_exn(
				trav.begin(),
				trav.end(),
				sanguis::client::perk::compare(
					fcppt::cast_to_enum<
						sanguis::perk_type
					>(
						item.get<
							messages::roles::perk_label
						>()
					)
				)
			)
		);

		pos->value(
			::make_info(
				item
			)
		);

		sanguis::messages::types::enum_vector const &children(
			item.get<sanguis::messages::roles::perk_children>()
		);

		for(
			auto const &child : children
		)
			pos->push_back(
				sanguis::client::perk::info(
					fcppt::cast_to_enum<
						sanguis::perk_type
					>(
						child
					)
				)
			);
	}

	return
		std::move(
			ret
		);
}

namespace
{

sanguis::client::perk::info const
make_info(
	sanguis::messages::perk_tree_node const &_node
)
{
	return
		sanguis::client::perk::info(
			fcppt::cast_to_enum<
				sanguis::perk_type
			>(
				_node.get<
					sanguis::messages::roles::perk_label
				>()
			),
			sanguis::client::perk::required_parent_level(
				sanguis::client::perk::level(
					sanguis::client::level(
						_node.get<
							sanguis::messages::roles::required_perk_parent_level
						>()
					)
				)
			),
			sanguis::client::perk::required_player_level(
				sanguis::client::player_level(
					sanguis::client::level(
						_node.get<
							sanguis::messages::roles::required_perk_player_level
						>()
					)
				)
			),
			sanguis::client::perk::max_level(
				sanguis::client::perk::level(
					sanguis::client::level(
						_node.get<
							sanguis::messages::roles::max_perk_level
						>()
					)
				)
			)
		);
}

}
