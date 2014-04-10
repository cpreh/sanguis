#ifndef SANGUIS_CLIENT_PERK_LEVEL_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_LEVEL_CALLBACK_HPP_INCLUDED

#include <sanguis/client/perk/level_function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace perk
{

typedef std::function<
	sanguis::client::perk::level_function
> level_callback;

}
}
}

#endif
