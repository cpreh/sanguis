#include "unpause.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::unpause, "unpause")

template<typename Archive>
void sanguis::messages::unpause::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<base>(*this);
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(unpause)
