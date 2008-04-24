#ifndef SANGUIS_SERVER_ENTITY_WITH_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITY_WITH_WEAPON_HPP_INCLUDED

#include "entity.hpp"
#include "weapons/weapon.hpp"
#include <boost/ptr_container/ptr_map.hpp>

namespace sanguis
{
namespace server
{

class entity_with_weapon : public entity {
protected:
	typedef boost::ptr_map<weapon_type::type,weapons::weapon> weapon_container;

	entity_with_weapon(
		send_callback const &,
		insert_callback const &,
		messages::pos_type const &pos,
		messages::space_unit angle,
		messages::space_unit direction,
		messages::space_unit health,
		messages::space_unit max_health,
		team::type team,
		messages::space_unit speed);

	virtual void update(
		time_type,
		entity_container &entities);
public:
	void change_weapon(const weapon_type::type);
	void add_weapon(weapons::weapon_ptr);
	void remove_weapon(const weapon_type::type);

	void target(messages::pos_type const&);
	messages::pos_type const &target() const;
private:
	weapon_container    weapons_;
	weapon_type::type   weapon_;
	messages::pos_type  target_;
};

}
}

#endif
