#ifndef SANGUIS_MESSAGES_ADD_PLAYER_BASIC_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_PLAYER_BASIC_FWD_HPP_INCLUDED

#include <sanguis/messages/add_with_buffs_fwd.hpp>
#include <sanguis/messages/bind_entity_message_fwd.hpp>
#include <sanguis/messages/types/message_fwd.hpp>
#include <majutsu/composite_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{

template<
	sanguis::messages::types::message Type
>
using add_player_basic
=
majutsu::composite<
	boost::mpl::vector2<
		sanguis::messages::bind_entity_message<
			Type
		>,
		sanguis::messages::add_with_buffs
	>
>;

}
}

#endif
