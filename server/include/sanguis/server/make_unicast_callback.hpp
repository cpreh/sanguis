#ifndef SANGUIS_SERVER_MAKE_UNICAST_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_MAKE_UNICAST_CALLBACK_HPP_INCLUDED

#include <sanguis/server/machine_fwd.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <fcppt/reference_fwd.hpp>


namespace sanguis
{
namespace server
{

sanguis::server::unicast_callback
make_unicast_callback(
	fcppt::reference<
		sanguis::server::machine
	>
);

}
}

#endif
