#ifndef SANGUIS_CLIENT_PERK_LEVEL_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_LEVEL_CALLBACK_HPP_INCLUDED

#include <sanguis/client/perk/level_function.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace client
{
namespace perk
{

typedef
fcppt::function<
	sanguis::client::perk::level_function
>
level_callback;

}
}
}

#endif
