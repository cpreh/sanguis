#ifndef SANGUIS_TO_CONSOLE_ARG_LIST_HPP_INCLUDED
#define SANGUIS_TO_CONSOLE_ARG_LIST_HPP_INCLUDED

#include <sanguis/string_vector.hpp>
#include <sge/console/arg_list.hpp>

namespace sanguis
{

sge::console::arg_list const
to_console_arg_list(
	sanguis::string_vector const &
);

}

#endif
