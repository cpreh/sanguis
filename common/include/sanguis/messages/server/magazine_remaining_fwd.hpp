#ifndef SANGUIS_MESSAGES_SERVER_MAGAZINE_REMAINING_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_MAGAZINE_REMAINING_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/is_primary_weapon_fwd.hpp>
#include <sanguis/messages/adapted_types/magazine_size_fwd.hpp>
#include <sanguis/messages/roles/is_primary_weapon.hpp>
#include <sanguis/messages/roles/magazine_remaining.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/record_fwd.hpp>
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
		sanguis::messages::server::types::message::magazine_remaining
	>,
	boost::mpl::vector2<
		fcppt::record::element<
			sanguis::messages::roles::is_primary_weapon,
			sanguis::messages::adapted_types::is_primary_weapon
		>,
		fcppt::record::element<
			sanguis::messages::roles::magazine_remaining,
			sanguis::messages::adapted_types::magazine_size
		>
	>
>
magazine_remaining;

}
}
}

#endif
