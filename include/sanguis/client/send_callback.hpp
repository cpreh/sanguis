#ifndef SANGUIS_CLIENT_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_SEND_CALLBACK_HPP_INCLUDED

#include <sanguis/messages/base_fwd.hpp>
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{

typedef fcppt::function::object<
	void(
		sanguis::messages::base const &
	)
> send_callback;

}
}

#endif
