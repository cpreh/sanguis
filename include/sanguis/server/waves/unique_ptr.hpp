#ifndef SANGUIS_SERVER_WAVES_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/waves/wave_fwd.hpp>
#include <fcppt/unique_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace waves
{

typedef fcppt::unique_ptr<
	wave
> unique_ptr;

}
}
}

#endif
