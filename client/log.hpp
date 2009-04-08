#ifndef SANGUIS_CLIENT_LOG_HPP_INCLUDED
#define SANGUIS_CLIENT_LOG_HPP_INCLUDED

// NOTE: no one gives a damn about minimally including logging stuff, logging
// is not a "main" activity. Thus, we include headers here so we don't have to
// worry about this stuff. Besides, if we change something in the sge (logging)
// api, we have to recompile the whole program anyway.
// Also, if you include this file, what are you gonna do? Yes, _log_ stuff! So
// you need the headers anyway.
#include <sge/log/headers.hpp>

namespace sanguis
{
namespace client
{

sge::log::logger &log();

}
}

#endif
