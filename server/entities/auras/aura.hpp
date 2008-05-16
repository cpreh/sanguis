#ifndef SANGUIS_SERVER_ENTITIES_AURAS_AURA_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_AURAS_AURA_HPP_INCLUDED

#include "../entity.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace auras
{

class aura : public entity {
protected:
	aura(
		environment const &,
		messages::pos_type const &pos,
		messages::space_unit radius,
		team::type team);
private:
	void update(
		time_type,
		container &entities);

	bool invulnerable() const;
	messages::space_unit max_speed() const;
	messages::dim_type dim() const;

	virtual void do_effect(entity &target) = 0;

	messages::space_unit radius_;
};

}
}
}
}

#endif
