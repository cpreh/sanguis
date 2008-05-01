#include "player_choose_perk.hpp"
#include "instantiate_serialize.hpp"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

BOOST_CLASS_EXPORT_GUID(sanguis::messages::player_choose_perk, "player_choose_perk")

sanguis::messages::player_choose_perk::player_choose_perk()
{}

sanguis::messages::player_choose_perk::player_choose_perk(
	const entity_id id,
	const enum_type perk_)
: entity_message(id),
  perk_(perk_)
{}

sanguis::messages::enum_type
sanguis::messages::player_choose_perk::perk() const
{
	return perk_;
}

template<typename Archive>
void sanguis::messages::player_choose_perk::serialize(
	Archive &ar,
	unsigned)
{
	ar & boost::serialization::base_object<entity_message>(*this)
	   & perk_;
}

SANGUIS_MESSAGES_INSTANTIATE_SERIALIZE(player_choose_perk)
