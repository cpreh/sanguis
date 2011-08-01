#ifndef SANGUIS_SERVER_WAVES_MAKE_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_MAKE_HPP_INCLUDED

#include "unique_ptr.hpp"
#include "../../diff_clock_fwd.hpp"
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
	fcppt::string const &
);

}
}
}

#endif
