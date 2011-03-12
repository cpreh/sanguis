#ifndef SANGUIS_MESSAGES_RESIZE_HPP_INCLUDED
#define SANGUIS_MESSAGES_RESIZE_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "dim.hpp"
#include "types/message.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector2<
		bind_entity_message<
			types::message::resize
		>::type,
		majutsu::role<
			dim
		>
	>
> resize_elements;

typedef make_class<
	resize_elements
>::type resize;

}
}

#endif
