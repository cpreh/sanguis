#ifndef SANGUIS_SERVER_UNICAST_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_UNICAST_CALLBACK_HPP_INCLUDED

#include "../net/id_type.hpp"
#include "../messages/auto_ptr.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{

typedef fcppt::function::object<
	void (
		net::id_type,
		messages::auto_ptr
	)
> unicast_callback;

}
}

#endif
