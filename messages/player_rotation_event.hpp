#ifndef SANGUIS_MESSAGES_PLAYER_ROTATION_EVENT_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_ROTATION_EVENT_INCLUDED

#include "../sge_serialization.hpp"
#include "base.hpp"
#include "types.hpp"
#include <boost/serialization/base_object.hpp>

namespace sanguis
{
namespace messages
{

class player_rotation_event : public base {
public:
	player_rotation_event();
	player_rotation_event(
		const entity_id,
		const space_unit angle);

	space_unit angle() const;
private:
	space_unit angle_;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned)
	{
		ar & boost::serialization::base_object<base>(*this);
		ar & angle_;
	}
};

}
}

#endif
