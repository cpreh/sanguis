#ifndef SANGUIS_SERVER_ENTITIES_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_BASE_HPP_INCLUDED

#include "base_fwd.hpp"
#include "link_container.hpp"
#include "auto_weak_link.hpp"
#include "insert_parameters_fwd.hpp"
#include "../pos_type.hpp"
#include "../space_unit.hpp"
#include "../team.hpp"
#include "../collision/base.hpp"
#include "../collision/global_groups_fwd.hpp"
#include "../collision/create_parameters_fwd.hpp"
#include "../environment/object_ptr.hpp"
#include "../../messages/auto_ptr.hpp"
#include "../../entity_id.hpp"
#include "../../entity_type.hpp"
#include "../../time_type.hpp"
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class base
:
	public collision::base
{
	SGE_NONCOPYABLE(base)
protected:
	base();
public:
	// general world functions
	
	void
	transfer(
		server::environment::object_ptr,
		collision::global_groups const &,
		insert_parameters const &
	);

	void
	update(
		time_type
	);

	void
	die();

	
	// linking with other objects
	
	auto_weak_link const
	link();


	// environment query function // TODO: should this be public?
	
	server::environment::object_ptr const
	environment() const;


	// entity id function
	
	entity_id
	id() const;


	// position and size functions

	space_unit
	angle() const;

	void
	angle(
		space_unit
	);

	pos_type const
	center() const;

	void
	center(
		pos_type const &
	);

	virtual space_unit
	radius() const = 0;


	// life functions
	
	virtual bool
	dead() const = 0;

	virtual bool
	invulnerable() const = 0;

	// message functions
	
	virtual messages::auto_ptr
	add_message() const = 0;


	// type query
	
	virtual entity_type::type
	type() const = 0;

	virtual server::team::type
	team() const = 0;

	virtual bool
	server_only() const;

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
		pos_type const &
	);

	virtual void
	on_transfer(
		collision::global_groups const &,
		collision::create_parameters const &
	);

	virtual pos_type const
	initial_direction() const;

	friend class auto_weak_link;

	sge::collision::shapes::container const
	recreate_shapes(
		sge::collision::world_ptr
	) const;
	
	collision::group_vector const
	collision_groups() const;

	void
	insert_link(
		auto_weak_link &
	);
	
	boost::logic::tribool const
	can_collide_with(
		collision::base const &
	) const;
	
	void
	collision_begin(
		collision::base &
	);

	void
	collision_end(
		collision::base &
	);

	virtual boost::logic::tribool const 
	can_collide_with_entity(
		base const &
	) const;
	
	virtual void
	collision_entity_begin(
		base &
	);

	virtual void
	collision_entity_end(
		base &
	);

	environment::object_ptr environment_;

	entity_id const id_;

	space_unit
		angle_,
		direction_;
	
	link_container links_;
};

}
}
}

#endif
