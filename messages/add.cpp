#include "add.hpp"
#include "instantiate_serialize.hpp"
#include "../sge_serialization.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::add, "add")

sanguis::messages::add::add()
{}

sanguis::messages::add::add(
	const entity_id id,
	const entity_type::type type_,
	const pos_type& pos_,
	const space_unit angle_,
	const vector2& speed_,
	const space_unit health_,
	const space_unit max_health_)
: entity_message(id),
  type_(type_),
  pos_(pos_),
  angle_(angle_),
  speed_(speed_),
  health_(health_),
  max_health_(max_health_)
{}
	
sanguis::entity_type::type sanguis::messages::add::type() const
{
	return type_;
}

const sanguis::messages::pos_type& sanguis::messages::add::pos() const
{
	return pos_;
}

const sanguis::messages::dim_type& sanguis::messages::add::dim() const
{
	return dim_;
}

sanguis::messages::space_unit sanguis::messages::add::angle() const
{
	return angle_;
}

const sanguis::messages::vector2& sanguis::messages::add::speed() const
{
	return speed_;
}

sanguis::messages::space_unit sanguis::messages::add::health() const
{
	return health_;
}

sanguis::messages::space_unit sanguis::messages::add::max_health() const
{
	return max_health_;
}

template<typename Archive>
void sanguis::messages::add::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this)
	   & type_
	   & pos_
	   & angle_
	   & speed_
	   & health_
	   & max_health_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(add)
