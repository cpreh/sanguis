#ifndef SANGUIS_MESSAGES_CLIENT_CHOOSE_PERK_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_CHOOSE_PERK_FWD_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/messages/adapted_types/enum_fwd.hpp>
#include <sanguis/messages/client/types/make_message_id_fwd.hpp>
#include <sanguis/messages/client/types/message.hpp>
#include <sanguis/messages/roles/perk_type.hpp>
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
		sanguis::messages::client::types::message::choose_perk
	>,
	boost::mpl::vector1<
		majutsu::role<
			sanguis::messages::adapted_types::enum_<
				sanguis::perk_type
			>,
			sanguis::messages::roles::perk_type
		>
	>
>
choose_perk;

}
}
}

#endif
