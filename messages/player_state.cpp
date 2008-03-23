#include "player_state.hpp"
#include "../archive.hpp"
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT(sanguis::messages::player_state)

sanguis::messages::player_state::player_state()
{}

sanguis::messages::player_state::player_state(
	const entity_id id,
	const sanguis::player_state &state)
: base(id),
  state(state)
{}
