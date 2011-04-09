#ifndef SANGUIS_CLIENT_PERK_CAST_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_CAST_HPP_INCLUDED

#include "perk_container.hpp"
#include "../messages/types/enum_vector.hpp"

namespace sanguis
{
namespace client
{

client::perk_container const
perk_cast(
	messages::types::enum_vector const &
);

}
}

#endif
