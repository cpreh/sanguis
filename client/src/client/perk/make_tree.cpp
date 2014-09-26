#include <sanguis/optional_perk_type.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/player_level.hpp>
#include <sanguis/client/perk/compare.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/make_tree.hpp>
#include <sanguis/client/perk/max_level.hpp>
#include <sanguis/client/perk/optional_info.hpp>
#include <sanguis/client/perk/required_parent_level.hpp>
#include <sanguis/client/perk/required_player_level.hpp>
#include <sanguis/client/perk/to_category.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <sanguis/messages/roles/max_perk_level.hpp>
#include <sanguis/messages/roles/perk_label.hpp>
#include <sanguis/messages/roles/perk_level.hpp>
#include <sanguis/messages/roles/perk_parent.hpp>
#include <sanguis/messages/roles/required_perk_parent_level.hpp>
#include <sanguis/messages/roles/required_perk_player_level.hpp>
#include <sanguis/messages/server/types/perk_tree_node_vector.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/find_if_exn.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/tree/pre_order.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

sanguis::client::perk::tree &
tree_position(
	sanguis::client::perk::tree &,
	sanguis::optional_perk_type
);

}


sanguis::client::perk::tree_unique_ptr
sanguis::client::perk::make_tree(
	sanguis::messages::server::types::perk_tree_node_vector const &_list
)
{
	// This code is highly dependent on the order in which the server sends
	// the perks

	sanguis::client::perk::tree_unique_ptr ret(
		fcppt::make_unique_ptr<
			sanguis::client::perk::tree
		>(
			sanguis::client::perk::optional_info()
		)
	);

	for(
		auto const &item
		:
		_list
	)
		::tree_position(
			*ret,
			item.get<
				sanguis::messages::roles::perk_parent
			>()
		).push_back(
			sanguis::client::perk::optional_info(
				sanguis::client::perk::info(
					item.get<
						sanguis::messages::roles::perk_label
					>(),
					sanguis::client::perk::level(
						sanguis::client::level(
							item.get<
								sanguis::messages::roles::perk_level
							>()
						)
					),
					sanguis::client::perk::required_parent_level(
						sanguis::client::perk::level(
							sanguis::client::level(
								item.get<
									sanguis::messages::roles::required_perk_parent_level
								>()
							)
						)
					),
					sanguis::client::perk::required_player_level(
						sanguis::client::player_level(
							sanguis::client::level(
								item.get<
									sanguis::messages::roles::required_perk_player_level
								>()
							)
						)
					),
					sanguis::client::perk::max_level(
						sanguis::client::perk::level(
							sanguis::client::level(
								item.get<
									sanguis::messages::roles::max_perk_level
								>()
							)
						)
					)
				)
			)
		);

	ret->sort(
		[](
			sanguis::client::perk::optional_info const &_left,
			sanguis::client::perk::optional_info const &_right
		)
		{
			return
				sanguis::client::perk::to_category(
					_left->perk_type()
				)
				<
				sanguis::client::perk::to_category(
					_right->perk_type()
				);
		}
	);

	return
		std::move(
			ret
		);
}

namespace
{

sanguis::client::perk::tree &
tree_position(
	sanguis::client::perk::tree &_tree,
	sanguis::optional_perk_type const _parent_enum
)
{
	if(
		!_parent_enum
	)
		return
			_tree;

	typedef fcppt::container::tree::pre_order<
		sanguis::client::perk::tree
	> traversal;

	traversal const trav(
		_tree
	);

	return
		*fcppt::algorithm::find_if_exn(
			trav.begin(),
			trav.end(),
			sanguis::client::perk::compare(
				*_parent_enum
			)
		);
}

}
