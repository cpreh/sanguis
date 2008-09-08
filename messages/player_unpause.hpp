#ifndef SANGUIS_MESSAGES_PLAYER_UNPAUSE_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_UNPAUSE_HPP_INCLUDED

#include "entity_message.hpp"
#include "types.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class player_unpause : public entity_message {
public:
	player_unpause();
	explicit player_unpause(
		entity_id);
private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
