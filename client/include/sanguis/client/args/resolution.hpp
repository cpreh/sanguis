#ifndef SANGUIS_CLIENT_ARGS_RESOLUTION_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_RESOLUTION_HPP_INCLUDED

#include <sanguis/client/args/optional_resolution.hpp>
#include <sanguis/client/args/result_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace args
{

sanguis::client::args::optional_resolution
resolution(
	sanguis::client::args::result const &
);

}
}
}

#endif
