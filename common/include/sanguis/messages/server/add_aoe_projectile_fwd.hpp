#ifndef SANGUIS_MESSAGES_SERVER_ADD_AOE_PROJECTILE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_ADD_AOE_PROJECTILE_FWD_HPP_INCLUDED

#include <sanguis/aoe_projectile_type_fwd.hpp>
#include <sanguis/messages/adapted_types/enum_fwd.hpp>
#include <sanguis/messages/adapted_types/space_unit_fwd.hpp>
#include <sanguis/messages/roles/aoe.hpp>
#include <sanguis/messages/roles/aoe_projectile_type.hpp>
#include <sanguis/messages/server/parts/add_elements_base_fwd.hpp>
#include <sanguis/messages/server/parts/entity_id_fwd.hpp>
#include <sanguis/messages/server/parts/speed_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/record_fwd.hpp>
#include <fcppt/mpl/flatten.hpp>
#include <fcppt/record/element_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

typedef
alda::message::record<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::add_aoe_projectile
	>,
	fcppt::mpl::flatten<
		boost::mpl::vector5<
			sanguis::messages::server::parts::entity_id,
			sanguis::messages::server::parts::add_elements_base,
			sanguis::messages::server::parts::speed,
			fcppt::record::element<
				sanguis::messages::roles::aoe,
				sanguis::messages::adapted_types::space_unit
			>,
			fcppt::record::element<
				sanguis::messages::roles::aoe_projectile_type,
				sanguis::messages::adapted_types::enum_<
					sanguis::aoe_projectile_type
				>
			>
		>
	>
>
add_aoe_projectile;

}
}
}

#endif
