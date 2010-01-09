#ifndef SANGUIS_CLIENT_MESSAGES_ADD_HPP_INCLUDED
#define SANGUIS_CLIENT_MESSAGES_ADD_HPP_INCLUDED

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
	explicit add(
		entity_type::type
	);

	entity_type::type
	type() const;
private:
	entity_type::type const type_;
};

}
}
}

#endif
