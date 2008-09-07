#ifndef SANGUIS_SERVER_ENTITY_WITH_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITY_WITH_WEAPON_HPP_INCLUDED

#include "entity.hpp"
#include "../weapons/weapon.hpp"
#include <boost/ptr_container/ptr_map.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class entity_with_weapon : public entity {
protected:
	typedef boost::ptr_map<
		weapon_type::type,
		weapons::weapon
	> weapon_container;

	entity_with_weapon(
		base_parameters const &,
		weapons::weapon_ptr start_weapon
			= weapons::weapon_ptr());

	virtual void update(
		time_type,
		container &entities);
public:
	void change_weapon(weapon_type::type);
	void add_weapon(weapons::weapon_ptr);
	void remove_weapon(weapon_type::type);

	void target(pos_type const&);
	pos_type const &target() const;
private:
	bool has_weapon() const;
	weapons::weapon &active_weapon();

	weapon_container    weapons_;
	weapon_type::type   weapon_;
	pos_type            target_;
};

}
}
}

#endif
