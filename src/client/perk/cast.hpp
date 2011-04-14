#ifndef SANGUIS_CLIENT_PERK_CAST_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_CAST_HPP_INCLUDED

#include "container.hpp"
#include "../../messages/types/enum_vector.hpp"

namespace sanguis
{
namespace client
{
namespace perk
{

perk::container const
cast(
	messages::types::enum_vector const &
);

}
}
}

#endif
