#ifndef SANGUIS_MESSAGES_PLAYER_CHOOSE_PERK_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_CHOOSE_PERK_HPP_INCLUDED

#include "entity_message.hpp"
#include "types.hpp"
#include "enum_type.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class player_choose_perk : public entity_message {
public:
	player_choose_perk();
	player_choose_perk(
		entity_id i,
		enum_type perk);
	enum_type perk() const;
private:
	enum_type perk_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
