#ifndef SANGUIS_CLIENT_MESSAGES_ADD_HPP_INCLUDED
#define SANGUIS_CLIENT_MESSAGES_ADD_HPP_INCLUDED

#include "../entity_id.hpp"
#include "../client_entity_type.hpp"

namespace sanguis
{
namespace client_messages
{

class add {
public:
	add(
		entity_id,
		client_entity_type::type);
	entity_id id() const;
	client_entity_type::type type() const;
private:
	entity_id                id_;
	client_entity_type::type type_;
};

}
}

#endif
