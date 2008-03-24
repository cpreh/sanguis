#include "base.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::base, "base")

sanguis::messages::base::base()
{}

sanguis::messages::base::~base()
{}

template<typename Archive>
void sanguis::messages::base::serialize(
	Archive &,
	unsigned)
{}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(base)
