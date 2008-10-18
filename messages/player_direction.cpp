#include "player_direction.hpp"
#include "instantiate_serialize.hpp"
#include "../sge_serialization.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::player_direction, "player_direction")

sanguis::messages::player_direction::player_direction()
:
	dir_(sge::no_initialization_tag())
{}

sanguis::messages::player_direction::player_direction(
	entity_id const id,
	vector2 const &dir_)
:
	entity_message(id),
	dir_(dir_)
{}
	
sanguis::messages::vector2 const &
sanguis::messages::player_direction::dir() const
{
	return dir_;
}

template<typename Archive>
void sanguis::messages::player_direction::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this)
	   & dir_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(player_direction)
