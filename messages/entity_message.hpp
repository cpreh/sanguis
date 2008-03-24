#ifndef SANGUIS_MESSAGES_ENTITY_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_ENTITY_MESSAGE_HPP_INCLUDED

#include "../entity_id.hpp"
#include "base.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class entity_message : public base {
public:
	entity_message();
	explicit entity_message(entity_id id);
	entity_id id() const;
private:
	entity_id id_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
