#ifndef SANGUIS_CLIENT_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_SEND_CALLBACK_HPP_INCLUDED

#include "../messages/auto_ptr.hpp"
#include <sge/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{

typedef sge::function::object<
	void (messages::auto_ptr)
> send_callback;

}
}

#endif
