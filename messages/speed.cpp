#include "speed.hpp"
#include "instantiate_serialize.hpp"
#include <sge/math/vector/serialize.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::speed, "speed")

sanguis::messages::speed::speed()
{}

sanguis::messages::speed::speed(
	entity_id const id,
	vector2 const &speed_)
:
	entity_message(id),
	speed_(speed_)
{}

sanguis::messages::vector2 const &
sanguis::messages::speed::get() const
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
