#include "experience.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::experience, "experience")

sanguis::messages::experience::experience()
{}

sanguis::messages::experience::experience(
	const entity_id id,
	const exp_type exp_)
: entity_message(id),
  exp_(exp_)
{}

sanguis::messages::exp_type
sanguis::messages::experience::exp() const
{
	return exp_;
}

template<typename Archive>
void sanguis::messages::experience::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this)
	   & exp_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(experience)
