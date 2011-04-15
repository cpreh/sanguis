#ifndef SANGUIS_CLIENT_PERK_TO_STRING_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_TO_STRING_HPP_INCLUDED

#include "../../perk_type.hpp"
#include <fcppt/string.hpp>

namespace sanguis
{
namespace client
{
namespace perk
{

fcppt::string const
to_string(
	sanguis::perk_type::type
);

}
}
}

#endif
