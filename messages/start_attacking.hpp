#ifndef SANGUIS_MESSAGES_START_ATTACKING_HPP_INCLUDED
#define SANGUIS_MESSAGES_START_ATTACKING_HPP_INCLUDED

#include "entity_message.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class start_attacking : public entity_message {
public:
	start_attacking();
	start_attacking(
		entity_id id);
private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
