#include "move.hpp"
#include "instantiate_serialize.hpp"
#include "../sge_serialization.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::move, "move")

sanguis::messages::move::move()
{}

sanguis::messages::move::move(
	entity_id const id,
	pos_type const &pos_)
:
	entity_message(id),
	pos_(pos_)
{}

sanguis::messages::pos_type const &
sanguis::messages::move::pos() const
{
	return pos_;
}

template<typename Archive>
void sanguis::messages::move::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this)
	   & pos_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(move)
