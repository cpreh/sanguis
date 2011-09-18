#ifndef SANGUIS_CLIENT_MAKE_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_MAKE_SEND_CALLBACK_HPP_INCLUDED

#include <sanguis/client/machine_fwd.hpp>
#include <sanguis/client/send_callback.hpp>

namespace sanguis
{
namespace client
{

client::send_callback const
make_send_callback(
	client::machine &
);

}
}

#endif
