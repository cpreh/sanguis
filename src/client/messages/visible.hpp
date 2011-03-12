#ifndef SANGUIS_CLIENT_MESSAGES_VISIBLE_HPP_INCLUDED
#define SANGUIS_CLIENT_MESSAGES_VISIBLE_HPP_INCLUDED

#include "visible_fwd.hpp"
#include "../../entity_id.hpp"
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace client
{
namespace messages
{

class visible
{
	FCPPT_NONASSIGNABLE(
		visible
	);
public:
	visible(
		entity_id,
		bool visible
	);

	entity_id
	id() const;

	bool
	get() const;
private:
	entity_id const id_;

	bool const visible_;
};

}
}
}

#endif
