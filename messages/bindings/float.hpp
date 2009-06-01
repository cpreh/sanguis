#ifndef SANGUIS_MESSAGES_BINDINGS_FLOAT_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_FLOAT_HPP_INCLUDED

#include "../types/space_unit.hpp"
#include <majutsu/raw_pointer.hpp>
#include <majutsu/size_type.hpp>

namespace sanguis
{
namespace messages
{
namespace bindings
{

struct float_ {
	typedef types::space_unit type;

	static majutsu::size_type
	needed_size(
		type const &);

	static void
	place(
		type const &t,
		majutsu::raw_pointer);

	static type
	make(
		majutsu::const_raw_pointer beg);
};

}
}
}

#endif
