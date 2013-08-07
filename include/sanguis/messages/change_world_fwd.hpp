#ifndef SANGUIS_MESSAGES_CHANGE_WORLD_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CHANGE_WORLD_FWD_HPP_INCLUDED

#include <sanguis/messages/make_class_fwd.hpp>
#include <sanguis/messages/make_message_id_fwd.hpp>
#include <sanguis/messages/seed_fwd.hpp>
#include <sanguis/messages/size_fwd.hpp>
#include <sanguis/messages/string_fwd.hpp>
#include <sanguis/messages/world_id_fwd.hpp>
#include <sanguis/messages/roles/generator_name.hpp>
#include <sanguis/messages/roles/opening_count.hpp>
#include <sanguis/messages/types/message.hpp>
#include <majutsu/composite_fwd.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{

typedef
sanguis::messages::make_class<
	majutsu::composite<
		boost::mpl::vector5<
			sanguis::messages::make_message_id<
				sanguis::messages::types::message::change_world
			>,
			majutsu::role<
				sanguis::messages::world_id
			>,
			majutsu::role<
				sanguis::messages::seed
			>,
			majutsu::role<
				sanguis::messages::string,
				sanguis::messages::roles::generator_name
			>,
			majutsu::role<
				sanguis::messages::size,
				sanguis::messages::roles::opening_count
			>
		>
	>
>
change_world;

}
}

#endif
