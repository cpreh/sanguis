#include "player_rotation.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::player_rotation, "player_rotation")

sanguis::messages::player_rotation::player_rotation()
{}

sanguis::messages::player_rotation::player_rotation(
	const entity_id id,
	const space_unit angle_)
: entity_message(id),
  angle_(angle_)
{}
	
sanguis::messages::space_unit sanguis::messages::player_rotation::angle() const
{
	return angle_;
}

template<typename Archive>
void sanguis::messages::player_rotation::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this)
	   & angle_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(player_rotation)
