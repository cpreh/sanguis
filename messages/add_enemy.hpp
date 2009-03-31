#ifndef SANGUIS_MESSAGES_ADD_ENEMY_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_ENEMY_HPP_INCLUDED

#include "make_add_message.hpp"
#include "make_class.hpp"
#include "enum.hpp"
#include "types/message.hpp"
#include "roles/enemy_type.hpp"
#include <majutsu/role.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef make_add_message<
	types::message::add_enemy,
	boost::mpl::vector<
		majutsu::role<
			enum_,
			roles::enemy_type
		>
	>
> add_enemy_elements;

typedef make_class<
	add_enemy_elements
> add_enemy;

}
}

#endif
