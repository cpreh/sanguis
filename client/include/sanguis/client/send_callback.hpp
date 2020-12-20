#ifndef SANGUIS_CLIENT_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_SEND_CALLBACK_HPP_INCLUDED

#include <sanguis/messages/client/base_fwd.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace client
{

using
send_callback
=
fcppt::function<
	void(
		sanguis::messages::client::base const &
	)
>;

}
}

#endif
