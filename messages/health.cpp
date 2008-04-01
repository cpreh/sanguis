#include "health.hpp"
#include "instantiate_serialize.hpp"
#include "../sge_serialization.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::health, "health")

sanguis::messages::health::health()
{}

sanguis::messages::health::health(
	const entity_id id,
	const space_unit value_)
: entity_message(id),
  value_(value_)
{}
	
sanguis::messages::space_unit sanguis::messages::health::value() const
{
	return value_;
}

template<typename Archive>
void sanguis::messages::health::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this)
	   & value_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(health)
