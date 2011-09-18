#ifndef SANGUIS_CLIENT_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_SEND_CALLBACK_HPP_INCLUDED

#include <sanguis/messages/auto_ptr.hpp>
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{

typedef fcppt::function::object<
	void (messages::auto_ptr)
> send_callback;

}
}

#endif
