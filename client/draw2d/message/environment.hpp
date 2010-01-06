#ifndef SANGUIS_CLIENT_DRAW_MESSAGE_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW_MESSAGE_ENVIRONMENT_HPP_INCLUDED

#include "entity_fwd.hpp"
#include "entity_auto_ptr.hpp"
#include "../exp_type.hpp"
#include "../level_type.hpp"
#include "../../entity_id.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{

class message_environment
{
	FCPPT_NONCOPYABLE(environment)
protected:
	message_environment();
public:
	virtual draw2d::entity &
	insert(
		entity_auto_ptr,
		entity_id
	) = 0;

	virtual draw2d::entity &
	entity(
		entity_id
	);

	virtual void
	experience(
		exp_type
	) = 0;

	virtual void
	level(
		level_type
	) = 0;

	virtual ~message_environment();
};

}
}
}

#endif
