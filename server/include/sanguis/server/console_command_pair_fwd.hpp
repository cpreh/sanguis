#ifndef SANGUIS_SERVER_CONSOLE_COMMAND_PAIR_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_CONSOLE_COMMAND_PAIR_FWD_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/tuple/object_fwd.hpp>

namespace sanguis::server
{

using console_command_pair = fcppt::tuple::object<fcppt::string, fcppt::string>;

}

#endif
