#ifndef SANGUIS_MESSAGES_ADD_PROJECTILE_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_PROJECTILE_HPP_INCLUDED

#include <sanguis/messages/roles/projectile.hpp>
#include <sanguis/messages/types/message.hpp>
#include <sanguis/messages/add_with_speed.hpp>
#include <sanguis/messages/bind_entity_message.hpp>
#include <sanguis/messages/make_class.hpp>
#include <sanguis/messages/enum.hpp>
#include <majutsu/role.hpp>
#include <majutsu/composite.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace messages
{

typedef messages::make_class<
	majutsu::composite<
		boost::mpl::vector3<
			messages::bind_entity_message<
				types::message::add_projectile
			>::type,
			messages::add_with_speed,
			majutsu::role<
				messages::enum_,
				roles::projectile
			>
		>
	>
>::type add_projectile;

}
}

#endif
