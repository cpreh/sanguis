#ifndef SANGUIS_CLIENT_DRAW2D_MESSAGE_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_MESSAGE_ENVIRONMENT_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "../entities/base_fwd.hpp"
#include "../entities/auto_ptr.hpp"
#include "../entities/model/parameters_fwd.hpp"
#include "../sprite/particle/system.hpp"
#include "../insert_callback.hpp"
#include "../transform_callback.hpp"
#include "../../exp_type.hpp"
#include "../../level_type.hpp"
#include "../../../entity_id.hpp"
#include <sge/renderer/screen_size.hpp>
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

	virtual void
	remove(
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

	virtual entities::model::parameters const
	model_parameters() const = 0;

	virtual sprite::particle::system &
	particle_system() const = 0;

	virtual draw2d::insert_callback const &
	insert_callback() const = 0;

	virtual draw2d::transform_callback const &
	transform_callback() const = 0;

	virtual sge::renderer::screen_size const
	screen_size() const = 0;

	virtual ~environment();
};

}
}
}
}

#endif
