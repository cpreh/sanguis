#ifndef SANGUIS_SERVER_ENTITIES_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_BASE_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
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

	void
	update();

	void
	remove();

	void
	destroy();

	// environment query function // TODO: should this be public?

	sanguis::server::environment::object &
	environment() const;

	bool
	has_environment() const;

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

	sanguis::server::environment::object *environment_;
};

}
}
}

#endif
