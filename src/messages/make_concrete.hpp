#ifndef SANGUIS_MESSAGES_MAKE_CONCRETE_HPP_INCLUDED
#define SANGUIS_MESSAGES_MAKE_CONCRETE_HPP_INCLUDED

#include "auto_ptr.hpp"
#include "concrete.hpp"

namespace sanguis
{
namespace messages
{

template<
	typename T
>
auto_ptr
make_concrete(
	T const &value
)
{
	return auto_ptr(
		new concrete<T>(
			value
		)
	);
}

}
}

#endif
