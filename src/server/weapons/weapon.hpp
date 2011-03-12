#ifndef SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED

#include "weapon_fwd.hpp"
#include "range.hpp"
#include "delayed_attack_fwd.hpp"
#include "magazine_size.hpp"
#include "magazine_count.hpp"
#include "base_cooldown.hpp"
#include "cast_point.hpp"
#include "reload_time.hpp"
#include "states/ready_fwd.hpp"
#include "states/reloading_fwd.hpp"
#include "states/backswing_fwd.hpp"
#include "states/castpoint_fwd.hpp"
#include "../pos_type.hpp"
#include "../space_unit.hpp"
#include "../entities/with_weapon_fwd.hpp"
#include "../entities/base_fwd.hpp"
#include "../../time_type.hpp"
#include "../../messages/base.hpp"
#include "../../weapon_type.hpp"
#include <sge/time/duration.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/statechart/state_machine.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{

class weapon
:
	public
		boost::statechart::state_machine<
			weapon,
			states::ready
		> 
{
	FCPPT_NONCOPYABLE(weapon)
public:
	weapons::range const
	range() const;

	void
	attack(
		entities::with_weapon &from,
		pos_type const &to
	);

	weapon_type::type
	type() const;

	void
	update(
		time_type,
		entities::with_weapon &owner
	);

	void stop();

	void repickup();

	weapons::magazine_size const
	magazine_size() const;

	bool
	in_range(
		entities::base const &from,
		pos_type const &to
	) const;

	void
	attack_speed(
		space_unit
	);

	void
	reload_speed(
		space_unit
	);

	virtual ~weapon();
protected:
	weapon(
		weapon_type::type,
		weapons::range,
		weapons::magazine_size,
		weapons::magazine_count,
		base_cooldown,
		weapons::cast_point,
		weapons::reload_time
	);

	virtual void
	do_attack(
		delayed_attack const &) = 0;
	
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

	sge::time::duration const
	cast_point() const;

	sge::time::duration const
	backswing_time() const;

	sge::time::duration const
	reload_time() const;

	virtual void
	init_attack(
		entities::with_weapon &owner
	);

	virtual void
	on_init_attack(
		entities::with_weapon &owner
	);

	virtual void
	on_castpoint(
		entities::with_weapon &owner
	);

	static fcppt::log::object &
	log();

	weapon_type::type const type_;
	weapons::range const range_;
	magazine_type magazine_used_;
	weapons::magazine_count magazine_count_;
	weapons::magazine_size const magazine_size_;
	sge::time::duration const
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