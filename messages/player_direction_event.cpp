#include "player_direction_event.hpp"
#include "../archive.hpp"
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT(sanguis::messages::player_direction_event)

sanguis::messages::player_direction_event::player_direction_event()
{}

sanguis::messages::player_direction_event::player_direction_event(
	const entity_id id,
	const vector2 &dir_)
: base(id),
  dir_(dir_)
{}
	
sanguis::messages::vector2 sanguis::messages::player_direction_event::dir() const
{
	return dir_;
}
