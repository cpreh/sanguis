#ifndef SANGUIS_CLIENT_CONFIG_SETTINGS_GET_OR_DEFAULT_HPP_INCLUDED
#define SANGUIS_CLIENT_CONFIG_SETTINGS_GET_OR_DEFAULT_HPP_INCLUDED

#include "object_fwd.hpp"
#include <fcppt/string.hpp>

namespace sanguis
{
namespace client
{
namespace config
{
namespace settings
{

fcppt::string const
get_or_default(
	object &,
	fcppt::string const &section,
	fcppt::string const &key,
	fcppt::string const &default_value
);

}
}
}
}

#endif
