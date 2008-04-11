#ifndef SANGUIS_MESSAGES_PLAYER_CHANGE_WEAPON_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_CHANGE_WEAPON_HPP_INCLUDED

#include "entity_message.hpp"
#include "types.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class player_change_weapon : public entity_message {
public:
	player_change_weapon();
	player_change_weapon(
		entity_id i,
		enum_type weapon);
	enum_type weapon() const;
private:
	enum_type weapon_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
