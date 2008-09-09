#include "add_decoration.hpp"
#include "instantiate_serialize.hpp"
#include "../sge_serialization.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::add_decoration, "add_decoration")

sanguis::messages::add_decoration::add_decoration()
{}

sanguis::messages::add_decoration::add_decoration(
	entity_id const id,
	decoration_type::type const ptype_,
	pos_type const &pos_,
	space_unit const angle_,
	space_unit const health_,
	space_unit const max_health_,
	dim_type const &dim_)
: add(
	id,
	entity_type::decoration,
	pos_,
	angle_,
	vector2(mu(0), mu(0)), // speed
	health_,
	max_health_,
	dim_),
  ptype_(ptype_)
{}

sanguis::decoration_type::type
sanguis::messages::add_decoration::ptype() const
{
	return ptype_;
}

template<typename Archive>
void sanguis::messages::add_decoration::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<add>(*this)
	   & ptype_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(add_decoration)
