#ifndef SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED

#include "delayed_attack_fwd.hpp"
#include "../environment.hpp"
#include "../pos_type.hpp"
#include "../space_unit.hpp"
#include "../entities/entity_with_weapon_fwd.hpp"
#include "../../time_type.hpp"
#include "../../messages/base.hpp"
#include "../../weapon_type.hpp"
#include "../../diff_clock.hpp"
#include <sge/time/timer.hpp>
#include <sge/log/logger.hpp>
#include <sge/noncopyable.hpp>
#include <boost/optional.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{
class weapon {
	SGE_NONCOPYABLE(weapon)
public:
	space_unit range() const;
	bool attack(
		entities::entity_with_weapon &from,
		pos_type const& to);
	weapon_type::type type() const;
	void update(
		time_type,
		entities::entity_with_weapon &owner);
	bool reloading() const;
	bool ready() const;
	unsigned magazine_size() const;

	bool in_range(
		entities::entity const &from,
		pos_type const& to) const;

	void attack_speed(
		space_unit);

	virtual ~weapon();
protected:
	weapon(
		server::environment const &,
		weapon_type::type,
		space_unit range,
		unsigned magazine_size,
		time_type base_cooldown,
		time_type cast_point,
		time_type reload_time);

	static unsigned const unlimited_magazine;

	virtual void do_attack(
		delayed_attack const &) = 0;
	
	entities::entity &insert(entities::auto_ptr);
	void send(
		messages::auto_ptr);
	server::environment const &
	environment() const;
private:
	virtual void on_init_attack(
		entities::entity_with_weapon &owner);
	virtual void on_castpoint(
		entities::entity_with_weapon &owner);

	static sge::log::logger &log();

	struct state {
		enum type {
			ready,
			castpoint,
			backswing,
			reload
		};
	};

	diff_clock              diff,
	                        ias_diff;
	server::environment     env_;
	weapon_type::type       type_;
	space_unit              range_;
	unsigned                magazine_used,
	                        magazine_size_;
	sge::time::timer        cooldown_timer,
	                        cast_point_timer,
	                        reload_timer;
	state::type             state_;
	space_unit              ias;

	boost::optional<
		pos_type
	>                       attack_dest;
};

}
}
}

#endif
