#ifndef SANGUIS_SERVER_ENTITIES_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_BASE_HPP_INCLUDED

#include "base_fwd.hpp"
#include "auto_weak_link.hpp"
#include "insert_parameters_fwd.hpp"
#include "link_container.hpp"
#include "transfer_parameters_fwd.hpp"
#include "../center.hpp"
#include "../player_id.hpp"
#include "../team.hpp"
#include "../collision/global_groups_fwd.hpp"
#include "../environment/object_fwd.hpp"
#include "../../messages/auto_ptr.hpp"
#include "../../entity_id.hpp"
#include "../../entity_type.hpp"
#include "../../time_type.hpp"
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
		entities::insert_parameters const &
	);

	void
	update(
		time_type
	);

	void
	remove();

	void
	destroy();

	// linking with other objects
	
	auto_weak_link const
	link();


	// environment query function // TODO: should this be public?
	
	server::environment::object &
	environment() const;

	bool
	has_environment() const;


	// entity id function
	
	sanguis::entity_id const
	id() const;


	// position and size functions

	virtual server::center const
	center() const = 0;

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
	on_create();

	virtual void
	on_remove();

	virtual void
	on_destroy();

	virtual void
	on_transfer(
		entities::transfer_parameters const &
	);

	friend class auto_weak_link;

	void
	insert_link(
		auto_weak_link &
	);
	
	environment::object *environment_;

	entity_id const id_;
	
	link_container links_;
};

}
}
}

#endif
