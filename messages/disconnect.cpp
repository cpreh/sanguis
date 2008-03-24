#include "disconnect.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT(sanguis::messages::disconnect)

sanguis::messages::disconnect::disconnect() {}

template<typename Archive>
void sanguis::messages::disconnect::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<base>(*this);
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(disconnect)
