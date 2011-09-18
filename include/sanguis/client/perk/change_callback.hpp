#ifndef SANGUIS_CLIENT_PERK_CHANGE_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_CHANGE_CALLBACK_HPP_INCLUDED

#include <sanguis/client/perk/change_function.hpp>
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace perk
{

typedef fcppt::function::object<
	perk::change_function
> change_callback;

}
}
}

#endif
