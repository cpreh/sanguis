#include "player_start_shooting.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::player_start_shooting, "player_start_shooting")

sanguis::messages::player_start_shooting::player_start_shooting()
{}

sanguis::messages::player_start_shooting::player_start_shooting(const entity_id id)
: entity_message(id)
{}

template<typename Archive>
void sanguis::messages::player_start_shooting::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this);
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(player_start_shooting)
