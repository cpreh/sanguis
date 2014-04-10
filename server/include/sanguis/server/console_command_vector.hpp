#ifndef SANGUIS_SERVER_CONSOLE_COMMAND_VECTOR_HPP_INCLUDED
#define SANGUIS_SERVER_CONSOLE_COMMAND_VECTOR_HPP_INCLUDED

#include <sanguis/server/console_command_pair.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{

typedef std::vector<
	sanguis::server::console_command_pair
> console_command_vector;

}
}

#endif
