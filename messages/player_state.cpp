#include "player_state.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::player_state, "player_state")

sanguis::messages::player_state::player_state()
{}

sanguis::messages::player_state::player_state(
	const entity_id id,
	const sanguis::player_state &state_)
: entity_message(id),
  state_(state_)
{}

sanguis::player_state const &
sanguis::messages::player_state::state() const
{
	return state_;
}

template<typename Archive>
void sanguis::messages::player_state::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this)
	   & state_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(player_state)
