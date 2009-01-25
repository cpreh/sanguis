#include "add_projectile.hpp"
#include "instantiate_serialize.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::add_projectile, "add_projectile")

sanguis::messages::add_projectile::add_projectile()
{}

sanguis::messages::add_projectile::add_projectile(
	entity_id const id,
	projectile_type::type const ptype_,
	pos_type const &pos_,
	space_unit const angle_,
	vector2 const &speed_,
	space_unit const health_,
	space_unit const max_health_,
	dim_type const &dim_)
:
	add(
		id,
		entity_type::projectile,
		pos_,
		angle_,
		speed_,
		health_,
		max_health_,
		dim_),
	ptype_(ptype_)
{}

sanguis::projectile_type::type
sanguis::messages::add_projectile::ptype() const
{
	return ptype_;
}

template<typename Archive>
void sanguis::messages::add_projectile::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<add>(*this)
	   & ptype_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(add_projectile)
