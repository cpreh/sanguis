#ifndef SANGUIS_MESSAGES_HEALTH_INCLUDED
#define SANGUIS_MESSAGES_HEALTH_INCLUDED

#include "entity_message.hpp"
#include "types.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class health : public entity_message {
public:
	health();
	health(
		const entity_id,
		const space_unit);

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
