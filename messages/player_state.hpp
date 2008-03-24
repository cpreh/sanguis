#ifndef SANGUIS_MESSAGES_PLAYER_STATE_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_STATE_HPP_INCLUDED

#include "../player_state.hpp"
#include "entity_message.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class player_state : public entity_message {
public:
	player_state();
	player_state(
		const entity_id,
		const sanguis::player_state &);
	const sanguis::player_state& state() const;
private:
	sanguis::player_state state_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
