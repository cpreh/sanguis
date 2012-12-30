#ifndef SANGUIS_SERVER_WAVES_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/waves/wave_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace waves
{

typedef std::unique_ptr<
	sanguis::server::waves::wave
> unique_ptr;

}
}
}

#endif
