#ifndef SANGUIS_MESSAGES_PLAYER_ROTATION_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_ROTATION_INCLUDED

#include "entity_message.hpp"
#include "types.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class player_rotation : public entity_message {
public:
	player_rotation();
	player_rotation(
		entity_id,
		space_unit angle);

	space_unit angle() const;
private:
	space_unit angle_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
