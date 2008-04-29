#include "level_change.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::level_change, "level_change")

sanguis::messages::level_change::level_change()
{}

sanguis::messages::level_change::level_change(
	const entity_id id,
	const level_type level_)
: entity_message(id),
  level_(level_)
{}

sanguis::messages::level_type
sanguis::messages::level_change::level() const
{
	return level_;
}

template<typename Archive>
void sanguis::messages::level_change::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this)
	   & level_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(level_change)
