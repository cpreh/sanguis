#include "game_state.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::game_state, "game_state")

sanguis::messages::game_state::game_state()
{}

sanguis::messages::game_state::game_state(
	const sanguis::game_state &state_)
: state_(state_)
{}

sanguis::game_state const &
sanguis::messages::game_state::state() const
{
	return state_;
}

template<typename Archive>
void sanguis::messages::game_state::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<base>(*this)
	   & state_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(game_state)
