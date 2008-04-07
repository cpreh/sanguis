#ifndef SANGUIS_MESSAGES_MAX_HEALTH_HPP_INCLUDED
#define SANGUIS_MESSAGES_MAX_HEALTH_HPP_INCLUDED

#include "entity_message.hpp"
#include "types.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class max_health : public entity_message {
public:
	max_health();
	max_health(
		entity_id,
		space_unit);
	space_unit value() const;
private:
	space_unit value_;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
