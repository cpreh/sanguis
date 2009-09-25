#ifndef SANGUIS_SERVER_AURAS_AURA_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_AURA_HPP_INCLUDED

#include "influence.hpp"
#include "../pos_type.hpp"
#include "../space_unit.hpp"
#include "../entities/base_fwd.hpp"
#include "../collision/base.hpp"
#include "../team.hpp"
#include "../../entity_id.hpp"
#include <sge/collision/shapes/container.hpp>
#include <sge/collision/world_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace auras
{

class aura
:
	public collision::base
{
public:
	virtual ~aura();

	void
	center(
		pos_type const &
	);

	void
	owner(
		entity_id
	);
protected:
	aura(
		space_unit radius,
		team::type,
		influence::type
	);
	
	entity_id
	owner() const;
private:
	sge::collision::shapes::container const
	recreate_shapes(
		sge::collision::world_ptr
	) const;

	virtual collision::group_vector const
	collision_groups() const;

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

	virtual void
	enter(
		entities::base &
	) = 0;

	virtual void
	leave(
		entities::base &
	) = 0;

	space_unit const radius_;
	team::type const team_;
	influence::type const influence_;
	entity_id owner_;
};

}
}
}

#endif
