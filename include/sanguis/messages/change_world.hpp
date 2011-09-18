#ifndef SANGUIS_MESSAGES_CHANGE_WORLD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CHANGE_WORLD_HPP_INCLUDED

#include <sanguis/messages/roles/generator_name.hpp>
#include <sanguis/messages/roles/world_size.hpp>
#include <sanguis/messages/types/message.hpp>
#include <sanguis/messages/dim2.hpp>
#include <sanguis/messages/make_class.hpp>
#include <sanguis/messages/make_message_id.hpp>
#include <sanguis/messages/seed.hpp>
#include <sanguis/messages/string.hpp>
#include <sanguis/messages/world_id.hpp>
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
		boost::mpl::vector5<
			messages::make_message_id<
				types::message::change_world
			>::type,
			majutsu::role<
				messages::world_id
			>,
			majutsu::role<
				messages::seed
			>,
			majutsu::role<
				messages::string,
				roles::generator_name
			>,
			majutsu::role<
				messages::dim2,
				roles::world_size
			>
		>
	>
>::type change_world;

}
}

#endif
