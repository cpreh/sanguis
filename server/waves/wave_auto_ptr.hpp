#ifndef SANGUIS_SERVER_WAVES_WAVE_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_WAVE_AUTO_PTR_HPP_INCLUDED

#include "wave_fwd.hpp"
#include <fcppt/auto_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace waves
{

typedef fcppt::auto_ptr<
	wave
> wave_auto_ptr;

}
}
}

#endif
