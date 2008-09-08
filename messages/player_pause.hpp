#ifndef SANGUIS_MESSAGES_PLAYER_PAUSE_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_PAUSE_HPP_INCLUDED

#include "entity_message.hpp"
#include "types.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class player_pause : public entity_message {
public:
	player_pause();
	explicit player_pause(
		entity_id);
private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
