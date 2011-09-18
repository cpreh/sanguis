#ifndef SANGUIS_SERVER_WAVES_DELAY_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_DELAY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sanguis
{
namespace server
{
namespace waves
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::duration,
	delay
);

}
}
}

#endif
