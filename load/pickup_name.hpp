#ifndef SANGUIS_LOAD_PICKUP_NAME_HPP_INCLUDED
#define SANGUIS_LOAD_PICKUP_NAME_HPP_INCLUDED

#include "../pickup_type.hpp"
#include <sge/string.hpp>
#include <boost/optional.hpp>

namespace sanguis
{
namespace load
{

boost::optional<sge::string> const
pickup_name(
	pickup_type::type);

}
}

#endif
