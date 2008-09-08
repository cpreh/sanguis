#include "give_weapon.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::give_weapon, "give_weapon")

sanguis::messages::give_weapon::give_weapon()
{}

sanguis::messages::give_weapon::give_weapon(
	entity_id const id,
	enum_type const weapon_,
	size_type const magazine_size_)
: entity_message(id),
  weapon_(weapon_),
  magazine_size_(magazine_size_)
{}

sanguis::messages::enum_type
sanguis::messages::give_weapon::weapon() const
{
	return weapon_;
}

sanguis::messages::size_type
sanguis::messages::give_weapon::magazine_size() const
{
	return magazine_size_;
}

template<typename Archive>
void sanguis::messages::give_weapon::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this)
	   & weapon_
	   & magazine_size_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(give_weapon)
