#include "entity_message.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::entity_message, "entity_id")

sanguis::messages::entity_message::entity_message()
{}

sanguis::messages::entity_message::entity_message(
	const entity_id id_)
: id_(id_)
{}

sanguis::entity_id
sanguis::messages::entity_message::id() const
{
	return id_;
}

void sanguis::messages::entity_message::id(
	const entity_id nid)
{
	id_ = nid;
}

template<typename Archive>
void sanguis::messages::entity_message::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<base>(*this)
	   & id_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(entity_message)
