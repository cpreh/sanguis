#ifndef SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED

#include "weapon_fwd.hpp"
#include "range.hpp"
#include "delayed_attack_fwd.hpp"
#include "magazine_type.hpp"
#include "states/ready_fwd.hpp"
#include "states/reloading_fwd.hpp"
#include "states/backswing_fwd.hpp"
#include "states/castpoint_fwd.hpp"
#include "../environment.hpp"
#include "../pos_type.hpp"
#include "../space_unit.hpp"
#include "../entities/entity_with_weapon_fwd.hpp"
#include "../../time_type.hpp"
#include "../../messages/base.hpp"
#include "../../weapon_type.hpp"
#include <sge/log/logger.hpp>
#include <sge/time/resolution.hpp>
#include <sge/noncopyable.hpp>
#include <boost/statechart/state_machine.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{

class weapon
: public
	boost::statechart::state_machine<
		weapon,
		states::ready
	> 
{
	SGE_NONCOPYABLE(weapon)
public:
	weapons::range const
	range() const;

	void
	attack(
		entities::entity_with_weapon &from,
		pos_type const &to);

	weapon_type::type
	type() const;

	void update(
		time_type,
		entities::entity_with_weapon &owner);

	void stop();

	void repickup();

	magazine_type	
	magazine_size() const;

	bool
	in_range(
		entities::entity const &from,
		pos_type const &to) const;

	void
	attack_speed(
		space_unit);

	void
	reload_speed(
		space_unit);

	virtual ~weapon();
protected:
	weapon(
		server::environment const &,
		weapon_type::type,
		weapons::range,
//		space_unit range,
		magazine_type magazine_size,
		magazine_type magazines_,
		time_type base_cooldown,
		time_type cast_point,
		time_type reload_time);

	static magazine_type const unlimited_magazine;

	virtual void
	do_attack(
		delayed_attack const &) = 0;
	
	entities::entity &
	insert(
		entities::auto_ptr);

	void send(
		messages::auto_ptr);

	server::environment const &
	environment() const;

	time_type
	ias() const;

	time_type
	irs() const;

	bool usable() const;
private:
	friend class states::ready;
	friend class states::reloading;
	friend class states::backswing;
	friend class states::castpoint;

	void
	reset_magazine();

	void
	use_magazine_item();

	bool
	magazine_empty() const;

	void
	magazine_exhausted();

	sge::time::resolution const
	cast_point() const;

	sge::time::resolution const
	backswing_time() const;

	sge::time::resolution const
	reload_time() const;

	virtual void
	init_attack(
		entities::entity_with_weapon &owner);

	virtual void
	on_init_attack(
		entities::entity_with_weapon &owner);

	virtual void
	on_castpoint(
		entities::entity_with_weapon &owner);

	static sge::log::logger &
	log();

	server::environment const env_;
	weapon_type::type const type_;
	weapons::range const range_;
	magazine_type
		magazine_used,
		magazines;
	magazine_type const magazine_size_;
	sge::time::resolution const
		cast_point_,
		backswing_time_,
		reload_time_;
	space_unit
		ias_,
		irs_;
};

}
}
}

#endif
