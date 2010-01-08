#ifndef SANGUIS_CLIENT_MESSAGES_ADD_HPP_INCLUDED
#define SANGUIS_CLIENT_MESSAGES_ADD_HPP_INCLUDED

#include "../../entity_id.hpp"
#include "../entity_type.hpp"

namespace sanguis
{
namespace client
{
namespace messages
{

class add
{
public:
	add(
		entity_id,
		entity_type::type
	);

	entity_id
	id() const;

	entity_type::type
	type() const;
private:
	entity_id const id_;
	entity_type::type const type_;
};

}
}
}

#endif
