#ifndef SANGUIS_MESSAGES_PLAYER_CHOOSE_PERK_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_CHOOSE_PERK_HPP_INCLUDED

#include <sanguis/messages/roles/perk.hpp>
#include <sanguis/messages/types/message.hpp>
#include <sanguis/messages/bind_player_message.hpp>
#include <sanguis/messages/enum.hpp>
#include <sanguis/messages/make_class.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace messages
{

typedef messages::make_class<
	majutsu::composite<
		boost::mpl::vector2<
			messages::bind_player_message<
				types::message::player_choose_perk
			>::type,
			majutsu::role<
				messages::enum_,
				roles::perk
			>
		>
	>
>::type player_choose_perk;

}
}

#endif
