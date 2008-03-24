#include "send_unique_id.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::send_unique_id, "send_unique_id")

sanguis::messages::send_unique_id::send_unique_id()
{}

sanguis::messages::send_unique_id::send_unique_id(
	const entity_id id)
: entity_message(id)
{}

template<typename Archive>
void sanguis::messages::send_unique_id::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this);
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(send_unique_id)
