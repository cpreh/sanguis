#include "player_change_weapon.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::player_change_weapon, "player_change_weapon")

sanguis::messages::player_change_weapon::player_change_weapon()
{}

sanguis::messages::player_change_weapon::player_change_weapon(
	const entity_id id,
	const enum_type weapon_)
: entity_message(id),
  weapon_(weapon_)
{}

sanguis::messages::enum_type
sanguis::messages::player_change_weapon::weapon() const
{
	return weapon_;
}

template<typename Archive>
void sanguis::messages::player_change_weapon::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this)
	   & weapon_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(player_change_weapon)
