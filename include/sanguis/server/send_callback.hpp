#ifndef SANGUIS_SERVER_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_SEND_CALLBACK_HPP_INCLUDED

#include <sanguis/messages/base_fwd.hpp>
#include <fcppt/function/object_fwd.hpp>


namespace sanguis
{
namespace server
{

typedef fcppt::function::object<
	void(
		messages::base const &
	)
> send_callback;

}
}

#endif
