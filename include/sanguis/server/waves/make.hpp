#ifndef SANGUIS_SERVER_WAVES_MAKE_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_MAKE_HPP_INCLUDED

#include <sanguis/server/waves/unique_ptr.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <fcppt/string.hpp>

namespace sanguis
{
namespace server
{
namespace waves
{

unique_ptr
make(
	sanguis::diff_clock const &,
	sanguis::random_generator &,
	fcppt::string const &
);

}
}
}

#endif
