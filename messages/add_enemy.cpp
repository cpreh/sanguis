#include "add_enemy.hpp"
#include "instantiate_serialize.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::add_enemy, "add_enemy")

sanguis::messages::add_enemy::add_enemy()
{}

sanguis::messages::add_enemy::add_enemy(
	entity_id const id,
	enemy_type::type const etype_,
	pos_type const &pos_,
	space_unit const angle_,
	vector2 const &speed_,
	space_unit const health_,
	space_unit const max_health_,
	dim_type const &dim_)
:
	add(
		id,
		entity_type::enemy,
		pos_,
		angle_,
		speed_,
		health_,
		max_health_,
		dim_),
	etype_(etype_)
{}

sanguis::enemy_type::type
sanguis::messages::add_enemy::etype() const
{
	return etype_;
}

template<typename Archive>
void sanguis::messages::add_enemy::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<add>(*this)
	   & etype_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(add_enemy)
