#include "game_state.hpp"
#include "../archive.hpp"
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT(sanguis::messages::game_state)

sanguis::messages::game_state::game_state(const sanguis::game_state &state)
: state(state)
{}
