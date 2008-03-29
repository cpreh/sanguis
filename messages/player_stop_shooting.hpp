#ifndef SANGUIS_MESSAGES_SPEED_HPP_INCLUDED
#define SANGUIS_MESSAGES_SPEED_HPP_INCLUDED

#include "entity_message.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class player_stop_shooting : public entity_message {
public:
	player_stop_shooting();
	player_stop_shooting(const entity_id);
private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
