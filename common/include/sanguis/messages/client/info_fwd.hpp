#ifndef SANGUIS_MESSAGES_CLIENT_INFO_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_INFO_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/string_fwd.hpp>
#include <sanguis/messages/client/types/make_message_id_fwd.hpp>
#include <sanguis/messages/client/types/message.hpp>
#include <sanguis/messages/roles/player_name.hpp>
#include <alda/message/make_class_fwd.hpp>
#include <majutsu/composite_fwd.hpp>
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
alda::message::make_class<
	majutsu::composite<
		boost::mpl::vector2<
			sanguis::messages::client::types::make_message_id<
				sanguis::messages::client::types::message::info
			>,
			majutsu::role<
				sanguis::messages::adapted_types::string,
				sanguis::messages::roles::player_name
			>
		>
	>
>
info;

}
}
}

#endif
