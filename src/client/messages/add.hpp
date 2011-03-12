#ifndef SANGUIS_CLIENT_MESSAGES_ADD_HPP_INCLUDED
#define SANGUIS_CLIENT_MESSAGES_ADD_HPP_INCLUDED

#include "add_fwd.hpp"
#include "../entity_type.hpp"
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace client
{
namespace messages
{

class add
{
	FCPPT_NONASSIGNABLE(
		add
	);
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
