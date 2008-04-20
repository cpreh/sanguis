#ifndef SANGUIS_TIME_UTIL_HPP_INCLUDED
#define SANGUIS_TIME_UTIL_HPP_INCLUDED

#include "time_type.hpp"
#include <sge/time.hpp>

namespace sanguis
{

sge::time_type to_sge_time(time_type);

}

#endif
