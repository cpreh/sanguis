#include "assign_id.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::assign_id, "assign_id")

sanguis::messages::assign_id::assign_id()
{}

sanguis::messages::assign_id::assign_id(
	entity_id const player_id_)
: player_id_(player_id_)
{}

sanguis::entity_id
sanguis::messages::assign_id::player_id() const
{
	return player_id_;
}

template<typename Archive>
void sanguis::messages::assign_id::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<base>(*this)
	   & player_id_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(assign_id)
