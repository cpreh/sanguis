#ifndef SANGUIS_SERVER_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_CREATE_HPP_INCLUDED

#include "../load/context_fwd.hpp"
#include "../net/port_type.hpp"
#include <sge/collision/system_ptr.hpp>

namespace sanguis
{
namespace server
{

main_object_auto_ptr
create(
	load::context const &,
	sge::collision::system_ptr,
	net::port_type host_port
);

}
}

#endif
