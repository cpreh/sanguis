#ifndef SANGUIS_SERVER_CONSOLE_PRINT_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_CONSOLE_PRINT_CALLBACK_HPP_INCLUDED

#include <sge/function/object_fwd.hpp>
#include <sge/string.hpp>

namespace sanguis
{
namespace server
{

typedef sge::function::object<
	void (
		sge::string
	)
> console_print_callback;

}
}

#endif
