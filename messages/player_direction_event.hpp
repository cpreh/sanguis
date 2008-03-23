#ifndef SANGUIS_MESSAGES_PLAYER_DIRECTION_EVENT_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_DIRECTION_EVENT_INCLUDED

#include "../sge_serialization.hpp"
#include "base.hpp"
#include "types.hpp"
#include <boost/serialization/base_object.hpp>

namespace sanguis
{
namespace messages
{

class player_direction_event : public base {
public:
	player_direction_event();
	player_direction_event(
		const entity_id,
		const vector2 &);

	vector2 dir() const;
private:
	vector2 dir_;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned)
	{
		ar & boost::serialization::base_object<base>(*this);
		ar & dir_;
	}
};

}
}

#endif
