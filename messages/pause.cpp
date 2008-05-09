#include "pause.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::pause, "pause")

template<typename Archive>
void sanguis::messages::pause::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<base>(*this);
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(pause)
