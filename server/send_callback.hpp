#ifndef SANGUIS_SERVER_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_SEND_CALLBACK_HPP_INCLUDED

#include "../messages/auto_ptr.hpp"
#include <sge/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{

typedef sge::function::object<
	void (messages::auto_ptr)
> send_callback;

}
}

#endif
