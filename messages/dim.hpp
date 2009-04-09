#ifndef SANGUIS_MESSAGES_DIM_HPP_INCLUDED
#define SANGUIS_MESSAGES_DIM_HPP_INCLUDED

#include "bindings/static.hpp"
#include "bindings/pod.hpp"
#include "types/dim.hpp"

namespace sanguis
{
namespace messages
{

typedef bindings::static_<
	types::dim,
	bindings::pod
> dim;

}
}

#endif
