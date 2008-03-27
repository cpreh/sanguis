#include "speed.hpp"
#include "instantiate_serialize.hpp"
#include "../sge_serialization.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::speed, "speed")

sanguis::messages::speed::speed()
{}

sanguis::messages::speed::speed(
	const entity_id id,
	const vector2& speed_)
: entity_message(id),
  speed_(speed_)
{}

const sanguis::messages::vector2& sanguis::messages::speed::get() const
{
	return speed_;
}

template<typename Archive>
void sanguis::messages::speed::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this)
	   & speed_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(speed)
