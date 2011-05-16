#ifndef SANGUIS_CLIENT_DRAW2D_MESSAGE_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_MESSAGE_ENVIRONMENT_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "../entities/base_fwd.hpp"
#include "../entities/unique_ptr.hpp"
#include "../entities/model/parameters_fwd.hpp"
#include "../sprite/particle/system.hpp"
#include "../insert_own_callback.hpp"
#include "../transform_callback.hpp"
#include "../../exp.hpp"
#include "../../level.hpp"
#include "../../world_parameters_fwd.hpp"
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
	FCPPT_NONCOPYABLE(
		environment
	);
protected:
	environment();
public:
	virtual entities::base &
	insert(
		entities::unique_ptr,
		sanguis::entity_id
	) = 0;

	virtual void
	remove(
		sanguis::entity_id
	) = 0;

	virtual entities::base &
	entity(
		sanguis::entity_id
	) = 0;

	virtual void
	experience(
		client::exp
	) = 0;

	virtual void
	level(
		client::level
	) = 0;

	virtual void
	change_world(
		client::world_parameters const &
	) = 0;

	virtual entities::model::parameters const
	model_parameters() const = 0;

	virtual sprite::particle::system &
	particle_system() const = 0;

	virtual draw2d::insert_own_callback const &
	insert_own_callback() const = 0;

	virtual draw2d::transform_callback const &
	transform_callback() const = 0;

	virtual ~environment();
};

}
}
}
}

#endif
