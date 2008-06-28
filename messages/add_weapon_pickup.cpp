#include "add_weapon_pickup.hpp"
#include "instantiate_serialize.hpp"
#include "../sge_serialization.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::add_weapon_pickup, "add_weapon_pickup")

sanguis::messages::add_weapon_pickup::add_weapon_pickup()
{}

sanguis::messages::add_weapon_pickup::add_weapon_pickup(
	entity_id const id,
	weapon_type::type const wtype_,
	pos_type const &pos_,
	space_unit const angle_,
	dim_type const &dim_)
: add(
	id,
	entity_type::pickup,
	pos_,
	angle_,
	vector2(mu(0), mu(0)), // speed
	mu(0), // health
	mu(0), // max_health
	dim_),
  wtype_(wtype_)
{}

sanguis::weapon_type::type
sanguis::messages::add_weapon_pickup::wtype() const
{
	return wtype_;
}

template<typename Archive>
void sanguis::messages::add_weapon_pickup::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<add>(*this)
	   & wtype_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(add_weapon_pickup)
