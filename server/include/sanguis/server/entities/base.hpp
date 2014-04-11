#ifndef SANGUIS_SERVER_ENTITIES_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_BASE_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/environment/optional_object_ref.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	// general world functions
	bool
	transfer(
		sanguis::server::environment::object &,
		sanguis::server::entities::insert_parameters const &,
		sanguis::creator::grid const &
	);

	virtual
	void
	world_collision(
		sanguis::creator::grid const &,
		sanguis::duration
	);

	virtual
	void
	update();

	/**
	\brief Called when the entity is removed from the game
	*/
	virtual
	void
	remove();

	/**
	\brief Called before the entity is deleted

	Some cleanup operations still need the entity in tact (and able to
	process virtual functions).
	*/
	virtual
	void
	destroy();

	/**
	\brief Called before an entity is transferred to another world

	This is different from remove or destroy because the entity is still
	alive but might need to invoke some callbacks by resetting its
	collision body.
	*/
	virtual
	void
	reset_body();

	// environment query function
	sanguis::server::environment::optional_object_ref const
	environment() const;

	// position
	virtual
	sanguis::server::center const
	center() const = 0;


	// life functions
	virtual
	bool
	dead() const = 0;

	virtual
	~base();
private:
	virtual
	void
	on_create();

	virtual
	bool
	on_transfer(
		sanguis::server::entities::transfer_parameters const &
	);

	sanguis::server::environment::optional_object_ref environment_;
};

}
}
}

#endif