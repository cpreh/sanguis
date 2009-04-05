#ifndef SANGUIS_MESSAGES_CREATE_HPP_INCLUDED
#define SANGUIS_MESSAGES_CREATE_HPP_INCLUDED

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
create(
	T const &t)
{
	return auto_ptr(
		new concrete<T>(
			t
		)
	);
}

}
}

#endif
