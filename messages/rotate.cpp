#include "rotate.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::rotate, "rotate")

sanguis::messages::rotate::rotate()
{}

sanguis::messages::rotate::rotate(
	const entity_id id,
	const space_unit rot_)
: entity_message(id),
  rot_(rot_)
{}

sanguis::messages::space_unit sanguis::messages::rotate::rot() const
{
	return rot_;
}

template<typename Archive>
void sanguis::messages::rotate::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this)
	   & rot_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(rotate)
