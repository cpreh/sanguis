#ifndef SANGUIS_SERVER_ENTITY_WITH_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITY_WITH_WEAPON_HPP_INCLUDED

#include "entity.hpp"
#include "weapons/weapon.hpp"

namespace sanguis
{
namespace server
{

class entity_with_weapon : public entity {
protected:
	entity_with_weapon(
		send_callback const &,
		insert_callback const &,
		messages::pos_type const &pos,
		messages::space_unit angle,
		messages::space_unit direction,
		messages::space_unit health,
		messages::space_unit max_health,
		team::type team,
		messages::space_unit speed,
		weapons::weapon_ptr);
	virtual void update(
		time_type,
		entity_container &entities);
public:
	void change_weapon(
		weapons::weapon_ptr);
	void target(
		messages::pos_type const&);
	messages::pos_type const &target() const;
private:
	weapons::weapon_ptr weapon_;
	messages::pos_type  target_;
};

}
}

#endif
