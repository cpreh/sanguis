#ifndef SANGUIS_SERVER_MAKE_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_MAKE_SEND_CALLBACK_HPP_INCLUDED

#include <sanguis/server/machine_fwd.hpp>
#include <sanguis/server/send_callback.hpp>


namespace sanguis
{
namespace server
{

sanguis::server::send_callback
make_send_callback(
	sanguis::server::machine &
);

}
}

#endif
