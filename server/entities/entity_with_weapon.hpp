#ifndef SANGUIS_SERVER_ENTITIES_ENTITY_WITH_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENTITY_WITH_WEAPON_HPP_INCLUDED

#include "entity.hpp"
#include "../weapons/auto_ptr.hpp"
#include "../../weapon_type.hpp"
#include <sge/signal/scoped_connection.hpp>
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
		weapons::auto_ptr start_weapon);

	virtual void update(
		time_type,
		container &entities);
public:
	void change_weapon(weapon_type::type);
	void add_weapon(weapons::auto_ptr);
	void remove_weapon(weapon_type::type);

	void target(pos_type const &);
	pos_type const &target() const;

	bool in_range(
		pos_type const &) const;

	bool has_weapon() const;
	weapons::weapon &active_weapon();
	weapons::weapon const &active_weapon() const;

	void start_attacking();

	void start_reloading();
	void stop_reloading();
private:
	void stop_attacking();

	void attack_speed_change(
		property::value_type);

	weapon_container    weapons_;
	weapon_type::type   weapon_;
	pos_type            target_;
	bool                attacking;
	sge::signal::scoped_connection const attack_speed_change_;
};

}
}
}

#endif
