#ifndef SANGUIS_SERVER_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_SEND_CALLBACK_HPP_INCLUDED

#include <sanguis/messages/server/base_fwd.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace server
{

typedef
fcppt::function<
	void(
		sanguis::messages::server::base const &
	)
>
send_callback;

}
}

#endif
