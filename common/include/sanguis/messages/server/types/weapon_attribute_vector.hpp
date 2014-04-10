#ifndef SANGUIS_MESSAGES_SERVER_TYPES_WEAPON_ATTRIBUTE_VECTOR_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_TYPES_WEAPON_ATTRIBUTE_VECTOR_HPP_INCLUDED

#include <sanguis/messages/server/types/weapon_attribute.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace types
{

typedef
std::vector<
	sanguis::messages::server::types::weapon_attribute
>
weapon_attribute_vector;

}
}
}
}

#endif
