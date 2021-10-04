#ifndef SANGUIS_SERVER_ENTITIES_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_BASE_HPP_INCLUDED

#include <sanguis/diff_clock.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/creator/grid_cref.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/optional_transfer_result_fwd.hpp>
#include <sanguis/server/entities/remove_from_world_result_fwd.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/transfer_result_fwd.hpp>
#include <sanguis/server/environment/object_ref.hpp>
#include <sanguis/server/environment/optional_object_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::entities
{

class base
{
	FCPPT_NONMOVABLE(
		base
	);
protected:
	base();
public:
	/**
	\brief Called when an entity is inserted into a world
	*/
	[[nodiscard]]
	sanguis::server::entities::optional_transfer_result
	transfer(
		sanguis::server::environment::object_ref,
		sanguis::server::entities::insert_parameters const &,
		sanguis::creator::grid_cref
	);

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
	[[nodiscard]]
	virtual
	sanguis::server::entities::remove_from_world_result
	remove_from_world();

	[[nodiscard]]
	sanguis::server::environment::optional_object_ref
	environment() const;

	[[nodiscard]]
	virtual
	sanguis::server::center
	center() const = 0;


	[[nodiscard]]
	virtual
	bool
	dead() const = 0;

	virtual
	~base();

	// TODO(philipp): Move this to another class?
	[[nodiscard]]
	sanguis::diff_clock const &
	diff_clock() const;
private:
	[[nodiscard]]
	virtual
	sanguis::server::entities::transfer_result
	on_create();

	[[nodiscard]]
	virtual
	sanguis::server::entities::optional_transfer_result
	on_transfer(
		sanguis::server::entities::transfer_parameters const &
	);

	// TODO(philipp): Move this to another class?
	sanguis::server::environment::optional_object_ref environment_;

	sanguis::diff_clock diff_clock_;
};

}

#endif
