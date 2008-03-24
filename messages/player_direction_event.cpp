#include "player_direction_event.hpp"
#include "instantiate_serialize.hpp"
#include "../sge_serialization.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::player_direction_event, "player_direction_event")

sanguis::messages::player_direction_event::player_direction_event()
{}

sanguis::messages::player_direction_event::player_direction_event(
	const entity_id id,
	const vector2 &dir_)
: entity_message(id),
  dir_(dir_)
{}
	
sanguis::messages::vector2 sanguis::messages::player_direction_event::dir() const
{
	return dir_;
}

template<typename Archive>
void sanguis::messages::player_direction_event::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this)
	   & dir_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(player_direction_event)
