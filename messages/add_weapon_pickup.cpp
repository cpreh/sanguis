#include "add_weapon_pickup.hpp"
#include "instantiate_serialize.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
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
	space_unit const health_,
	space_unit const max_health_,
	dim_type const &dim_)
:
	add(
		id,
		entity_type::pickup,
		pos_,
		angle_,
		vector2::null(), // speed
		health_,
		max_health_,
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
