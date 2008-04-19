#ifndef SANGUIS_MESSAGES_PLAYER_DIRECTION_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_DIRECTION_HPP_INCLUDED

#include "entity_message.hpp"
#include "types.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class player_direction : public entity_message {
public:
	player_direction();
	player_direction(
		const entity_id,
		const vector2 &);

	vector2 dir() const;
private:
	vector2 dir_;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
