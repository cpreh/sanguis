#ifndef SANGUIS_FROM_CONSOLE_ARG_LIST_HPP_INCLUDED
#define SANGUIS_FROM_CONSOLE_ARG_LIST_HPP_INCLUDED

#include <sanguis/string_vector.hpp>
#include <sge/console/arg_list.hpp>


namespace sanguis
{

sanguis::string_vector
from_console_arg_list(
	sge::console::arg_list const &
);

}

#endif
