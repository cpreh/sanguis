#include "add_pickup.hpp"
#include "instantiate_serialize.hpp"
#include "../sge_serialization.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::add_pickup, "add_pickup")

sanguis::messages::add_pickup::add_pickup()
{}

sanguis::messages::add_pickup::add_pickup(
	entity_id const id,
	pickup_type::type const ptype_,
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
  ptype_(ptype_)
{}

sanguis::pickup_type::type
sanguis::messages::add_pickup::ptype() const
{
	return ptype_;
}

template<typename Archive>
void sanguis::messages::add_pickup::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<add>(*this)
	   & ptype_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(add_pickup)
