#include <sanguis/exception.hpp>
#include <sanguis/optional_perk_type.hpp>
#include <sanguis/perk_type.hpp>
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
#include <sanguis/client/perk/to_string.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <sanguis/messages/roles/max_perk_level.hpp>
#include <sanguis/messages/roles/perk_label.hpp>
#include <sanguis/messages/roles/perk_level.hpp>
#include <sanguis/messages/roles/perk_parent.hpp>
#include <sanguis/messages/roles/required_perk_parent_level.hpp>
#include <sanguis/messages/roles/required_perk_player_level.hpp>
#include <sanguis/messages/server/types/perk_tree_node_vector.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_if_exn.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/tree/pre_order.hpp>


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
		fcppt::make_unique_ptr_fcppt<
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
					FCPPT_ASSERT_OPTIONAL_ERROR(
						_left
					).perk_type()
				)
				<
				sanguis::client::perk::to_category(
					FCPPT_ASSERT_OPTIONAL_ERROR(
						_right
					).perk_type()
				);
		}
	);

	return
		ret;
}

namespace
{

sanguis::client::perk::tree &
tree_position(
	sanguis::client::perk::tree &_tree,
	sanguis::optional_perk_type const _parent_enum
)
{
	return
		fcppt::maybe(
			_parent_enum,
			[
				&_tree
			]()
			->
			sanguis::client::perk::tree &
			{
				return
					_tree;
			},
			[
				&_tree
			](
				sanguis::perk_type const _parent_type
			)
			->
			sanguis::client::perk::tree &
			{
				return
					*fcppt::algorithm::find_if_exn(
						fcppt::container::tree::pre_order<
							sanguis::client::perk::tree
						>(
							_tree
						),
						sanguis::client::perk::compare(
							_parent_type
						),
						[
							_parent_type
						]{
							return
								sanguis::exception{
									FCPPT_TEXT("Can't find tree position of perk ")
									+
									sanguis::client::perk::to_string(
										_parent_type
									)
								};
						}
					);
			}
		);
}

}
