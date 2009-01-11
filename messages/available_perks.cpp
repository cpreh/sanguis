#include "available_perks.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::available_perks, "available_perks")

sanguis::messages::available_perks::available_perks()
{}

sanguis::messages::available_perks::available_perks(
	perk_list const &perks_)
:
	perks_(perks_)
{}

sanguis::messages::perk_list const &
sanguis::messages::available_perks::perks() const
{
	return perks_;
}

template<typename Archive>
void sanguis::messages::available_perks::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this)
	   & perks_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(available_perks)
