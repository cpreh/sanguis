#ifndef SANGUIS_MESSAGES_CLIENT_ATTACK_DEST_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_ATTACK_DEST_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/vector2_fwd.hpp>
#include <sanguis/messages/client/types/make_message_id.hpp>
#include <sanguis/messages/client/types/message.hpp>
#include <sanguis/messages/roles/attack_dest.hpp>
#include <alda/bindings/record_variadic_fwd.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{

using
attack_dest
=
alda::message::object<
	sanguis::messages::client::types::make_message_id<
		sanguis::messages::client::types::message::attack_dest
	>,
	alda::bindings::record_variadic<
		fcppt::record::element<
			sanguis::messages::roles::attack_dest,
			sanguis::messages::adapted_types::vector2
		>
	>
>;

}
}
}

#endif
