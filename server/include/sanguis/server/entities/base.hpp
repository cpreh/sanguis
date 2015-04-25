#ifndef SANGUIS_SERVER_ENTITIES_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_BASE_HPP_INCLUDED

#include <sanguis/diff_clock.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/optional_transfer_result_fwd.hpp>
#include <sanguis/server/entities/remove_from_world_result_fwd.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/transfer_result_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/environment/optional_object_ref.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/warn_unused_result.hpp>


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
	/**
	\brief Called when an entity is inserted into a world
	*/
	sanguis::server::entities::optional_transfer_result
	transfer(
		sanguis::server::environment::object &,
		sanguis::server::entities::insert_parameters const &,
		sanguis::creator::grid const &
	)
	FCPPT_PP_WARN_UNUSED_RESULT;

	virtual
	void
	update();

	virtual
	void
	tick(
		sanguis::duration const &
	);

	/**
	\brief Called when the entity is removed from the game
	*/
	virtual
	void
	remove_from_game();

	/**
	\brief Called before an entity is removed from a world
	*/
	virtual
	sanguis::server::entities::remove_from_world_result
	remove_from_world()
	FCPPT_PP_WARN_UNUSED_RESULT;

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

	// TODO: Move this to another class?
	sanguis::diff_clock const &
	diff_clock() const;
private:
	virtual
	sanguis::server::entities::transfer_result
	on_create()
	FCPPT_PP_WARN_UNUSED_RESULT;

	virtual
	sanguis::server::entities::optional_transfer_result
	on_transfer(
		sanguis::server::entities::transfer_parameters const &
	)
	FCPPT_PP_WARN_UNUSED_RESULT;

	// TODO: Move this to another class?
	sanguis::server::environment::optional_object_ref environment_;

	sanguis::diff_clock diff_clock_;
};

}
}
}

#endif
