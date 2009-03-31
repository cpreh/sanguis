#ifndef SANGUIS_MESSAGES_ADD_DECORATION_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_DECORATION_HPP_INCLUDED

#include "make_add_message.hpp"
#include "make_class.hpp"
#include "enum.hpp"
#include "types/message.hpp"
#include "roles/decoration.hpp"
#include <majutsu/role.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef make_add_message<
	types::message::add_decoration,
	boost::mpl::vector<
		majutsu::role<
			enum_,
			roles::decoration
		>
	>
> add_decoration_elements;

typedef make_class<
	add_decoration_elements
> add_decoration;

}
}

#endif
