#include <sanguis/entity_id.hpp>
#include <sanguis/client/exp.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/transform_callback.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/message/environment.hpp>
#include <sanguis/client/draw2d/scene/hud.hpp>
#include <sanguis/client/draw2d/scene/message_environment.hpp>
#include <sanguis/client/draw2d/scene/object.hpp>
#include <sanguis/client/draw2d/scene/world/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::message_environment::message_environment(
	sanguis::client::draw2d::scene::object &_object,
	sanguis::client::draw2d::scene::hud &_hud,
	sanguis::client::draw2d::scene::world::object &_world
)
:
	sanguis::client::draw2d::message::environment(),
	object_(
		_object
	),
	hud_(
		_hud
	),
	world_(
		_world
	)
{
}

sanguis::client::draw2d::scene::message_environment::~message_environment()
{
}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::scene::message_environment::insert(
	sanguis::client::draw2d::entities::unique_ptr &&_entity,
	sanguis::entity_id const _id
)
{
	return
		object_.insert(
			std::move(
				_entity
			),
			_id
		);
}

void
sanguis::client::draw2d::scene::message_environment::remove(
	sanguis::entity_id const _id
)
{
	object_.remove(
		_id
	);
}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::scene::message_environment::entity(
	sanguis::entity_id const _id
)
{
	return
		object_.entity(
			_id
		);
}

void
sanguis::client::draw2d::scene::message_environment::experience(
	sanguis::client::exp const _exp
)
{
	hud_.experience(
		_exp
	);
}

void
sanguis::client::draw2d::scene::message_environment::level(
	sanguis::client::level const _level
)
{
	hud_.level(
		_level
	);
}

void
sanguis::client::draw2d::scene::message_environment::change_world(
	sanguis::client::world_parameters const &_param
)
{
	world_.change(
		_param
	);
}

sanguis::client::draw2d::entities::model::parameters const
sanguis::client::draw2d::scene::message_environment::model_parameters() const
{
	return
		sanguis::client::draw2d::entities::model::parameters(
			object_.diff_clock(),
			object_.random_generator(),
			object_.colored_system(),
			object_.normal_system(),
			object_.load_collection()
		);
}

sanguis::client::draw2d::insert_own_callback const &
sanguis::client::draw2d::scene::message_environment::insert_own_callback() const
{
	return
		object_.insert_own_callback();
}

sanguis::client::draw2d::transform_callback const &
sanguis::client::draw2d::scene::message_environment::transform_callback() const
{
	return
		object_.transform_callback();
}

sanguis::client::draw2d::collide_callback const &
sanguis::client::draw2d::scene::message_environment::collide_callback() const
{
	return
		world_.collide_callback();
}
