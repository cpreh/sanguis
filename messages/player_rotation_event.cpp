#include "player_rotation_event.hpp"
#include "../archive.hpp"
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT(sanguis::messages::player_rotation_event)

sanguis::messages::player_rotation_event::player_rotation_event()
{}

sanguis::messages::player_rotation_event::player_rotation_event(
	const entity_id id,
	const space_unit angle_)
: base(id),
  angle_(angle_)
{}
	
sanguis::messages::space_unit sanguis::messages::player_rotation_event::angle() const
{
	return angle_;
}
