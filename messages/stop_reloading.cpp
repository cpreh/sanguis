#include "stop_reloading.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::stop_reloading, "stop_reloading")

sanguis::messages::stop_reloading::stop_reloading()
{}

sanguis::messages::stop_reloading::stop_reloading(
	entity_id const id)
: entity_message(id)
{}

template<typename Archive>
void sanguis::messages::stop_reloading::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this);
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(stop_reloading)
