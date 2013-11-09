#ifndef SANGUIS_CLIENT_DRAW2D_MESSAGE_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_MESSAGE_ENVIRONMENT_HPP_INCLUDED

#include <sanguis/entity_id_fwd.hpp>
#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/client/exp.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/player_center_callback.hpp>
#include <sanguis/client/draw2d/entities/base_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/message/environment_fwd.hpp>
#include <sanguis/load/auras/context_fwd.hpp>
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
	virtual
	sanguis::client::draw2d::entities::base &
	insert(
		sanguis::client::draw2d::entities::unique_ptr &&,
		sanguis::entity_id
	) = 0;

	virtual
	void
	remove(
		sanguis::entity_id
	) = 0;

	virtual
	sanguis::client::draw2d::entities::base &
	entity(
		sanguis::entity_id
	) = 0;

	virtual
	void
	experience(
		sanguis::client::exp
	) = 0;

	virtual
	void
	level(
		sanguis::client::level
	) = 0;

	virtual
	void
	change_world(
		sanguis::client::world_parameters const &
	) = 0;

	virtual
	void
	give_weapon(
		sanguis::weapon_description const &
	) = 0;

	virtual
	void
	remove_weapon(
		sanguis::is_primary_weapon
	) = 0;

	virtual
	sanguis::client::draw2d::entities::model::load_parameters const
	model_parameters() const = 0;

	virtual
	sanguis::load::auras::context &
	aura_resources() const = 0;

	virtual
	sanguis::client::draw2d::insert_own_callback const &
	insert_own_callback() const = 0;

	virtual
	sanguis::client::draw2d::player_center_callback const &
	player_center_callback() const = 0;

	virtual
	sanguis::client::draw2d::collide_callback const &
	collide_callback() const = 0;

	virtual
	~environment() = 0;
};

}
}
}
}

#endif
