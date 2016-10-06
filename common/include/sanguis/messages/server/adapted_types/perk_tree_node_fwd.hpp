#ifndef SANGUIS_MESSAGES_SERVER_ADAPTED_TYPES_PERK_TREE_NODE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_ADAPTED_TYPES_PERK_TREE_NODE_FWD_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/messages/adapted_types/enum_fwd.hpp>
#include <sanguis/messages/adapted_types/level_fwd.hpp>
#include <sanguis/messages/roles/max_perk_level.hpp>
#include <sanguis/messages/roles/perk_label.hpp>
#include <sanguis/messages/roles/perk_level.hpp>
#include <sanguis/messages/roles/perk_parent.hpp>
#include <sanguis/messages/roles/required_perk_parent_level.hpp>
#include <sanguis/messages/roles/required_perk_player_level.hpp>
#include <alda/bindings/optional_fwd.hpp>
#include <alda/bindings/record_variadic_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace adapted_types
{

typedef
alda::bindings::record_variadic<
	fcppt::record::element<
		sanguis::messages::roles::perk_label,
		sanguis::messages::adapted_types::enum_<
			sanguis::perk_type
		>
	>,
	fcppt::record::element<
		sanguis::messages::roles::perk_level,
		sanguis::messages::adapted_types::level
	>,
	fcppt::record::element<
		sanguis::messages::roles::required_perk_player_level,
		sanguis::messages::adapted_types::level
	>,
	fcppt::record::element<
		sanguis::messages::roles::required_perk_parent_level,
		sanguis::messages::adapted_types::level
	>,
	fcppt::record::element<
		sanguis::messages::roles::max_perk_level,
		sanguis::messages::adapted_types::level
	>,
	fcppt::record::element<
		sanguis::messages::roles::perk_parent,
		alda::bindings::optional<
			sanguis::perk_type,
			sanguis::messages::adapted_types::enum_<
				sanguis::perk_type
			>
		>
	>
>
perk_tree_node;

}
}
}
}

#endif
