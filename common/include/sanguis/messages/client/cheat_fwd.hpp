#ifndef SANGUIS_MESSAGES_CLIENT_CHEAT_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_CHEAT_FWD_HPP_INCLUDED

#include <sanguis/cheat_type_fwd.hpp>
#include <sanguis/messages/adapted_types/enum_fwd.hpp>
#include <sanguis/messages/client/types/make_message_id.hpp>
#include <sanguis/messages/client/types/message.hpp>
#include <sanguis/messages/roles/cheat_type.hpp>
#include <alda/message/record_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>
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
		sanguis::messages::client::types::message::cheat
	>,
	boost::mpl::vector1<
		fcppt::record::element<
			sanguis::messages::roles::cheat_type,
			sanguis::messages::adapted_types::enum_<
				sanguis::cheat_type
			>
		>
	>
>
cheat;

}
}
}

#endif
