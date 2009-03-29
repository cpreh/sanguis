#ifndef SANGUIS_MESSAGES_ENTITY_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_ENTITY_MESSAGE_HPP_INCLUDED

#include "entity_id.hpp"
#include "message_type.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector<
		message_type,
		majutsu::role<
			entity_id
		>
	>
> entity_message;
/*
class entity_message : public base {
public:
	entity_message();
	explicit entity_message(
		entity_id id);
	entity_id id() const;
	void id(entity_id);
private:
	entity_id id_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};
*/

}
}

#endif
