#ifndef SANGUIS_CLIENT_PERK_LEVEL_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_LEVEL_CALLBACK_HPP_INCLUDED

#include <sanguis/client/perk/level_function.hpp>
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace perk
{

typedef fcppt::function::object<
	perk::level_function
> level_callback;

}
}
}

#endif
