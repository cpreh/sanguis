#ifndef SANGUIS_CLIENT_PERK_CAST_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_CAST_HPP_INCLUDED

#include "../messages/types/enum_vector.hpp"
#include "perk_container.hpp"

namespace sanguis
{
namespace client
{
perk_container const perk_cast(
	messages::types::enum_vector const &);
}
}

#endif // SANGUIS_CLIENT_PERK_CAST_HPP_INCLUDED
