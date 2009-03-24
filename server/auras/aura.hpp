#ifndef SANGUIS_SERVER_AURAS_AURA_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_AURA_HPP_INCLUDED

#include "influence.hpp"
#include "../environment_fwd.hpp"
#include "../entities/entity_fwd.hpp"
#include "../collision/base.hpp"
#include "../teams.hpp"
#include "../types.hpp"
#include "../../entity_id.hpp"

namespace sanguis
{
namespace server
{
namespace auras
{

class aura : public collision::base {
public:
	virtual ~aura();

	void center(
		pos_type const &);
	void owner(
		entity_id);
protected:
	aura(
		environment const &,
		space_unit radius,
		team::type team,
		influence::type);
	
	entity_id
	owner() const;
private:
	bool
	can_collide_with(
		collision::base const &) const;

	void
	collision(
		collision::base &);

	virtual void
	do_effect(
		entities::entity &) = 0;

	team::type const      team_;
	influence::type const influence_;
	entity_id owner_;
};

}
}
}

#endif
