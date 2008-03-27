#include "request_unique_id.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::request_unique_id, "request_unique_id")

sanguis::messages::request_unique_id::request_unique_id()
{}

sanguis::messages::request_unique_id::request_unique_id(
	const size_type num_ids_)
: num_ids_(num_ids_)
{}

sanguis::messages::size_type
sanguis::messages::request_unique_id::num_ids() const
{
	return num_ids_;
}

template<typename Archive>
void sanguis::messages::request_unique_id::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<base>(*this)
	   & num_ids_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(request_unique_id)
