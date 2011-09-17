#ifndef SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED

#include "weapon_fwd.hpp"
#include "backswing_time.hpp"
#include "base_cooldown.hpp"
#include "cast_point.hpp"
#include "delayed_attack_fwd.hpp"
#include "magazine_size.hpp"
#include "magazine_count.hpp"
#include "range.hpp"
#include "reload_time.hpp"
#include "states/ready_fwd.hpp"
#include "states/reloading_fwd.hpp"
#include "states/backswing_fwd.hpp"
#include "states/castpoint_fwd.hpp"
#include "../vector.hpp"
#include "../entities/with_weapon_fwd.hpp"
#include "../entities/base_fwd.hpp"
#include "../../messages/base.hpp"
#include "../../diff_clock_fwd.hpp"
#include "../../duration.hpp"
#include "../../time_unit.hpp"
#include "../../weapon_type.hpp"
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
	FCPPT_NONCOPYABLE(
		weapon
	);
public:
	weapons::range const
	range() const;

	void
	attack(
		entities::with_weapon &from,
		server::vector const &to
	);

	weapon_type::type
	type() const;

	void
	update(
		entities::with_weapon &owner
	);

	void
	stop();

	void
	repickup();

	weapons::magazine_size const
	magazine_size() const;

	bool
	in_range(
		entities::base const &from,
		server::vector const &to
	) const;

	void
	attack_speed(
		sanguis::time_unit
	);

	void
	reload_speed(
		sanguis::time_unit
	);

	virtual ~weapon();
protected:
	weapon(
		sanguis::diff_clock const &,
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
		delayed_attack const &
	) = 0;

	bool
	usable() const;

	sanguis::diff_clock const &
	diff_clock() const;
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

	weapons::cast_point const
	cast_point() const;

	weapons::backswing_time const
	backswing_time() const;

	weapons::reload_time const
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

	sanguis::diff_clock const &diff_clock_;

	weapon_type::type const type_;

	weapons::range const range_;

	magazine_type magazine_used_;

	weapons::magazine_count::value_type magazine_count_;

	weapons::magazine_size const magazine_size_;

	weapons::cast_point const cast_point_;

	weapons::backswing_time const backswing_time_;

	weapons::reload_time const reload_time_;

	sanguis::time_unit
		ias_,
		irs_;
};

}
}
}

#endif
