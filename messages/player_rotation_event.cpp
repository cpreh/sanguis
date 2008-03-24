#include "player_rotation_event.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::player_rotation_event, "player_rotation_event")

sanguis::messages::player_rotation_event::player_rotation_event()
{}

sanguis::messages::player_rotation_event::player_rotation_event(
	const entity_id id,
	const space_unit angle_)
: entity_message(id),
  angle_(angle_)
{}
	
sanguis::messages::space_unit sanguis::messages::player_rotation_event::angle() const
{
	return angle_;
}

template<typename Archive>
void sanguis::messages::player_rotation_event::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this)
	   & angle_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(player_rotation_event)
