#ifndef SANGUIS_MESSAGES_CONVERT_FROM_WEAPON_ATTRIBUTE_VECTOR_HPP_INCLUDED
#define SANGUIS_MESSAGES_CONVERT_FROM_WEAPON_ATTRIBUTE_VECTOR_HPP_INCLUDED

#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/common/symbol.hpp>
#include <sanguis/messages/server/types/weapon_attribute_vector.hpp>


namespace sanguis
{
namespace messages
{
namespace convert
{

SANGUIS_COMMON_SYMBOL
sanguis::weapon_attribute_vector
from_weapon_attribute_vector(
	sanguis::messages::server::types::weapon_attribute_vector const &
);

}
}
}

#endif
