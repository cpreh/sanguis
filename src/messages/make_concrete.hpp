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
messages::auto_ptr
make_concrete(
	T const &_value
)
{
	return
		messages::auto_ptr(
			new messages::concrete<
				T
			>(
				_value
			)
		);
}

}
}

#endif
