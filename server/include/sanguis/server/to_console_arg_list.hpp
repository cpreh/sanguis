#ifndef SANGUIS_SERVER_TO_CONSOLE_ARG_LIST_HPP_INCLUDED
#define SANGUIS_SERVER_TO_CONSOLE_ARG_LIST_HPP_INCLUDED

#include <sanguis/string_vector.hpp>
#include <sge/console/arg_list.hpp>


namespace sanguis
{
namespace server
{

sge::console::arg_list
to_console_arg_list(
	sanguis::string_vector const &
);

}
}

#endif
