#include "remove.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::remove, "remove")

sanguis::messages::remove::remove()
{}

sanguis::messages::remove::remove(
	const entity_id id)
: entity_message(id)
{}

template<typename Archive>
void sanguis::messages::remove::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this);
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(remove)
