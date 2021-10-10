#ifndef SANGUIS_CLIENT_PERK_TO_STRING_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_TO_STRING_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>
#include <fcppt/string.hpp>

namespace sanguis::client::perk
{

fcppt::string to_string(sanguis::perk_type);

}

#endif
