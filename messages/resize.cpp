#include "resize.hpp"
#include "instantiate_serialize.hpp"
#include "../sge_serialization.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::resize, "resize")

sanguis::messages::resize::resize()
{}

sanguis::messages::resize::resize(
	entity_id const id,
	dim_type const &dim_)
:
	entity_message(id),
	dim_(dim_)
{}

sanguis::messages::dim_type const &
sanguis::messages::resize::dim() const
{
	return dim_;
}

template<typename Archive>
void sanguis::messages::resize::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this)
	   & dim_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(resize)
