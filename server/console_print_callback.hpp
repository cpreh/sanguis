#ifndef SANGUIS_SERVER_CONSOLE_PRINT_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_CONSOLE_PRINT_CALLBACK_HPP_INCLUDED

#include <sge/string.hpp>
#include <boost/function.hpp>

namespace sanguis
{
namespace server
{

typedef boost::function<void (sge::string)> console_print_callback;

}
}

#endif
