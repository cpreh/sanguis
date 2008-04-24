#include "add_weapon.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::add_weapon, "add_weapon")

sanguis::messages::add_weapon::add_weapon()
{}

sanguis::messages::add_weapon::add_weapon(
	const entity_id id,
	const enum_type weapon_)
: entity_message(id),
  weapon_(weapon_)
{}

sanguis::messages::enum_type
sanguis::messages::add_weapon::weapon() const
{
	return weapon_;
}

template<typename Archive>
void sanguis::messages::add_weapon::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this)
	   & weapon_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(add_weapon)
