#ifndef SANGUIS_MESSAGES_LEVEL_TYPE_HPP_INCLUDED
#define SANGUIS_MESSAGES_LEVEL_TYPE_HPP_INCLUDED

#include "types/level.hpp"
#include "bindings/pod.hpp"

namespace sanguis
{
namespace messages
{

typedef bindings::pod<
	types::level
> level_type;

}
}

#endif
