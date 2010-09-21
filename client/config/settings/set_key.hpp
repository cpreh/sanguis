#ifndef SANGUIS_CLIENT_CONFIG_SETTINGS_SET_KEY_HPP_INCLUDED
#define SANGUIS_CLIENT_CONFIG_SETTINGS_SET_KEY_HPP_INCLUDED

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

void
set_key(
	object &,
	fcppt::string const &section,
	fcppt::string const &key,
	fcppt::string const &value
);

}
}
}
}

#endif