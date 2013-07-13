#ifndef SANGUIS_SERVER_ENTITIES_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_BASE_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/collision/result_fwd.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/link_container.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
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
		sanguis::server::collision::result const &
	);

	void
	update();

	void
	remove();

	void
	destroy();

	// linking with other objects

	sanguis::server::entities::auto_weak_link const
	link();


	// environment query function // TODO: should this be public?

	sanguis::server::environment::object &
	environment() const;

	bool
	has_environment() const;


	// position and size functions

	virtual
	sanguis::server::center const
	center() const = 0;


	// life functions

	virtual
	bool
	dead() const = 0;

	// type query

	virtual
	sanguis::server::team
	team() const = 0;

	virtual
	~base();
private:
	virtual
	void
	on_update();

	virtual
	void
	on_create();

	virtual
	void
	on_remove();

	virtual
	void
	on_destroy();

	virtual
	bool
	on_transfer(
		sanguis::server::entities::transfer_parameters const &
	);

	friend class sanguis::server::entities::auto_weak_link;

	void
	insert_link(
		sanguis::server::entities::auto_weak_link &
	);

	sanguis::server::environment::object *environment_;

	sanguis::server::entities::link_container links_;
};

}
}
}

#endif
