#ifndef SANGUIS_MESSAGES_LEVEL_CHANGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_LEVEL_CHANGE_HPP_INCLUDED

#include "entity_message.hpp"
#include "types.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class level_change : public entity_message {
public:
	level_change();
	level_change(
		entity_id id,
		level_type level);
	level_type level() const;
private:
	level_type level_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
