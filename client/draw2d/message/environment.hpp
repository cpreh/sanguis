#ifndef SANGUIS_CLIENT_DRAW2D_MESSAGE_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_MESSAGE_ENVIRONMENT_HPP_INCLUDED

#include "../entities/base_fwd.hpp"
#include "../entities/auto_ptr.hpp"
#include "../../exp_type.hpp"
#include "../../level_type.hpp"
#include "../../../entity_id.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace message
{

class environment
{
	FCPPT_NONCOPYABLE(environment)
protected:
	environment();
public:
	virtual entities::base &
	insert(
		entities::auto_ptr,
		entity_id
	) = 0;

	virtual entities::base &
	entity(
		entity_id
	) = 0;

	virtual void
	experience(
		exp_type
	) = 0;

	virtual void
	level(
		level_type
	) = 0;

	virtual ~environment();
};

}
}
}
}

#endif
