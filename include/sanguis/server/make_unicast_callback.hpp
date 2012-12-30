#ifndef SANGUIS_SERVER_MAKE_UNICAST_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_MAKE_UNICAST_CALLBACK_HPP_INCLUDED

#include <sanguis/server/machine_fwd.hpp>
#include <sanguis/server/unicast_callback.hpp>


namespace sanguis
{
namespace server
{

sanguis::server::unicast_callback const
make_unicast_callback(
	sanguis::server::machine &
);

}
}

#endif
