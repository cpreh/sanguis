#include "request_unique_id.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::request_unique_id, "request_unique_id")

template<typename Archive>
void sanguis::messages::request_unique_id::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<base>(*this);
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(request_unique_id)
