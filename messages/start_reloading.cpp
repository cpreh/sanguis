#include "start_reloading.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::start_reloading, "start_reloading")

sanguis::messages::start_reloading::start_reloading()
{}

sanguis::messages::start_reloading::start_reloading(
	entity_id const id)
: entity_message(id)
{}

template<typename Archive>
void sanguis::messages::start_reloading::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this);
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(start_reloading)
