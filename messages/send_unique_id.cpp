#include "send_unique_id.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::send_unique_id, "send_unique_id")

sanguis::messages::send_unique_id::send_unique_id()
{}

sanguis::messages::send_unique_id::send_unique_id(
	const id_vector& ids_)
: ids_(ids_)
{}

sanguis::messages::send_unique_id::id_vector const &
sanguis::messages::send_unique_id::ids() const
{
	return ids_;
}

template<typename Archive>
void sanguis::messages::send_unique_id::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<base>(*this)
	   & ids_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(send_unique_id)
