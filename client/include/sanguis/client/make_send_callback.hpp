#ifndef SANGUIS_CLIENT_MAKE_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_MAKE_SEND_CALLBACK_HPP_INCLUDED

#include <sanguis/client/machine_fwd.hpp>
#include <sanguis/client/send_callback.hpp>
#include <fcppt/reference_fwd.hpp>


namespace sanguis::client
{

sanguis::client::send_callback
make_send_callback(
	fcppt::reference<
		sanguis::client::machine
	>
);

}

#endif
