#ifndef SANGUIS_SERVER_AURAS_AURA_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_AURA_HPP_INCLUDED

#include "influence.hpp"
#include "../pos_type.hpp"
#include "../space_unit.hpp"
#include "../entities/base_fwd.hpp"
#include "../collision/ghost_base.hpp"
#include "../collision/ghost_unique_ptr.hpp"
#include "../collision/group_vector.hpp"
#include "../collision/global_groups_fwd.hpp"
#include "../team.hpp"
#include "../../entity_id.hpp"
#include <sge/projectile/world_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace auras
{

class aura
{
	FCPPT_NONCOPYABLE(
		aura
	);
public:
	virtual ~aura();

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
	virtual collision::group_vector const
	collision_groups() const;

	boost::logic::tribool const
	can_collide_with(
		collision::body_base const &
	) const;

	void
	collision_begin(
		collsion::body_base &
	);

	void
	collision_end(
		collsion::body_base &
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

	typedef fcppt::scoped_ptr<
		collision::ghost
	> ghost_scoped_ptr;

	ghost_scoped_ptr ghost_;
};

}
}
}

#endif
