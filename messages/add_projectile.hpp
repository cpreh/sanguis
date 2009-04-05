#ifndef SANGUIS_MESSAGES_ADD_PROJECTILE_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_PROJECTILE_HPP_INCLUDED

#include "make_add_message.hpp"
#include "make_class.hpp"
#include "enum.hpp"
#include "types/message.hpp"
#include "roles/projectile.hpp"
#include <majutsu/role.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef make_add_message<
	types::message::add_projectile,
	boost::mpl::vector<
		majutsu::role<
			enum_,
			roles::projectile
		>
	>
>::type add_projectile_elements;

typedef make_class<
	add_projectile_elements
>::type add_projectile;

}
}

#endif
