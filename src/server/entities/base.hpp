#ifndef SANGUIS_SERVER_ENTITIES_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_BASE_HPP_INCLUDED

#include "base_fwd.hpp"
#include "auto_weak_link.hpp"
#include "insert_parameters_fwd.hpp"
#include "link_container.hpp"
#include "../pos.hpp"
#include "../player_id.hpp"
#include "../space_unit.hpp"
#include "../team.hpp"
#include "../collision/global_groups_fwd.hpp"
#include "../environment/object_fwd.hpp"
#include "../../messages/auto_ptr.hpp"
#include "../../entity_id.hpp"
#include "../../entity_type.hpp"
#include "../../time_type.hpp"
#include <sge/projectile/shape/base_ptr.hpp>
#include <sge/projectile/world_fwd.hpp>
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
	
	void
	transfer(
		server::environment::object &,
		collision::global_groups const &,
		insert_parameters const &
	);

	void
	update(
		time_type
	);

	void
	die();

	bool
	processed() const;
	
	void
	may_be_deleted();

	
	// linking with other objects
	
	auto_weak_link const
	link();


	// environment query function // TODO: should this be public?
	
	server::environment::object_ptr const
	environment() const;

	bool
	is_in_world() const;


	// entity id function
	
	sanguis::entity_id
	id() const;


	// position and size functions

	server::space_unit
	angle() const;

	void
	angle(
		server::space_unit
	);

	server::pos const
	center() const;

	void
	center(
		server::pos const &
	);

	virtual bool
	server_only() const;


	// life functions
	
	virtual bool
	dead() const = 0;

	// message functions
	
	virtual messages::auto_ptr
	add_message(
		player_id
	) const = 0;


	// type query
	
	virtual entity_type::type
	type() const = 0;

	virtual server::team::type
	team() const = 0;

	virtual ~base();
private:
	virtual void
	on_update(
		time_type
	);

	virtual void
	on_die();

	virtual void
	on_center(
		server::pos const &
	);

	virtual void
	on_transfer(
		collision::global_groups const &,
		collision::create_parameters const &
	);

	virtual server::pos const
	initial_direction() const;

	friend class auto_weak_link;

	void
	insert_link(
		auto_weak_link &
	);
	
	environment::object *environment_;

	entity_id const id_;

	space_unit angle_;

	bool processed_;
	
	link_container links_;
};

}
}
}

#endif
