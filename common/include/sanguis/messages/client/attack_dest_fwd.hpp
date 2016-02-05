#ifndef SANGUIS_MESSAGES_CLIENT_ATTACK_DEST_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_ATTACK_DEST_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/vector2_fwd.hpp>
#include <sanguis/messages/client/types/make_message_id.hpp>
#include <sanguis/messages/client/types/message.hpp>
#include <sanguis/messages/roles/attack_dest.hpp>
#include <alda/message/record_fwd.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{

typedef
alda::message::record<
	sanguis::messages::client::types::make_message_id<
		sanguis::messages::client::types::message::attack_dest
	>,
	boost::mpl::vector1<
		majutsu::role<
			sanguis::messages::adapted_types::vector2,
			sanguis::messages::roles::attack_dest
		>
	>
>
attack_dest;

}
}
}

#endif
