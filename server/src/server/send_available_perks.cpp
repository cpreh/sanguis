#include <sanguis/optional_perk_type.hpp>
#include <sanguis/messages/roles/max_perk_level.hpp>
#include <sanguis/messages/roles/perk_label.hpp>
#include <sanguis/messages/roles/perk_level.hpp>
#include <sanguis/messages/roles/perk_parent.hpp>
#include <sanguis/messages/roles/perk_tree.hpp>
#include <sanguis/messages/roles/remaining_perk_levels.hpp>
#include <sanguis/messages/roles/required_perk_parent_level.hpp>
#include <sanguis/messages/roles/required_perk_player_level.hpp>
#include <sanguis/messages/server/available_perks.hpp>
#include <sanguis/messages/server/create.hpp>
#include <sanguis/messages/server/types/perk_tree_node.hpp>
#include <sanguis/messages/server/types/perk_tree_node_vector.hpp>
#include <sanguis/server/send_available_perks.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/perks/tree/object.hpp>
#include <sanguis/server/perks/tree/status.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/algorithm/map_concat.hpp>
#include <fcppt/container/tree/pre_order.hpp>


void
sanguis::server::send_available_perks(
	sanguis::server::entities::player const &_player,
	sanguis::server::unicast_callback const &_send
)
{
	sanguis::messages::server::types::perk_tree_node_vector const nodes(
		fcppt::algorithm::map_concat<
			sanguis::messages::server::types::perk_tree_node_vector
		>(
			_player.perk_tree(),
			[](
				sanguis::server::perks::tree::object const &_tree
			)
			{
				return
					fcppt::algorithm::map<
						sanguis::messages::server::types::perk_tree_node_vector
					>(
						fcppt::container::tree::pre_order<
							sanguis::server::perks::tree::object const
						>(
							_tree
						),
						[](
							sanguis::server::perks::tree::object const &_inner
						)
						{
							sanguis::server::perks::tree::status const &info(
								_inner.value()
							);

							return
								sanguis::messages::server::types::perk_tree_node(
									sanguis::messages::roles::perk_label{} =
										info.type(),
									sanguis::messages::roles::perk_level{} =
										info.level().get(),
									sanguis::messages::roles::required_perk_player_level{} =
										info.required_player_level().get(),
									sanguis::messages::roles::required_perk_parent_level{} =
										info.required_parent_level().get(),
									sanguis::messages::roles::max_perk_level{} =
										info.max_level().get(),
									sanguis::messages::roles::perk_parent{} =
										_inner.parent().has_value()
										?
											sanguis::optional_perk_type(
												_inner.parent()->value().type()
											)
										:
											sanguis::optional_perk_type()
								);
						}
					);
			}
		)
	);

	_send(
		_player.player_id(),
		sanguis::messages::server::create(
			sanguis::messages::server::available_perks(
				sanguis::messages::roles::perk_tree{} =
					nodes,
				sanguis::messages::roles::remaining_perk_levels{} =
					_player.skill_points().get()
			)
		)
	);
}
