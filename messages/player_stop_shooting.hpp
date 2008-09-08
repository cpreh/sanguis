#ifndef SANGUIS_MESSAGES_PLAYER_STOP_SHOOTING_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_STOP_SHOOTING_HPP_INCLUDED

#include "entity_message.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class player_stop_shooting : public entity_message {
public:
	player_stop_shooting();
	explicit player_stop_shooting(
		entity_id);
private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
