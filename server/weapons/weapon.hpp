#ifndef SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED

#include "../../time_type.hpp"
#include "../../messages/base.hpp"
#include "../../weapon_type.hpp"
#include "../../diff_clock.hpp"
#include "../types.hpp"
#include "../environment.hpp"
#include "../entities/entity_fwd.hpp"
#include <sge/time/timer.hpp>
#include <boost/optional.hpp>
#include <memory>

namespace sanguis
{
namespace server
{
namespace weapons
{

class delayed_attack;

class weapon {
public:
	space_unit range() const;
	bool attack(
		entities::entity const &from,
		pos_type const& to);
	weapon_type::type type() const;
	void update(
		time_type,
		entities::entity const &owner);
	virtual ~weapon();
protected:
	weapon(
		environment const &,
		weapon_type::type,
		space_unit range,
		time_type base_cooldown,
		time_type cast_point);

	virtual void do_attack(
		delayed_attack const &) = 0;
	
	entities::entity &insert(entities::auto_ptr);
	void send(
		messages::auto_ptr);
	environment get_environment() const;
private:
	bool in_range(
		entities::entity const& from,
		pos_type const& to) const;

	diff_clock              diff;
	environment             env_;
	weapon_type::type       type_;
	space_unit              range_;
	sge::time::timer        cooldown_timer,
	                        cast_point_timer;
	boost::optional<
		pos_type>       attack_dest;
};

typedef std::auto_ptr<weapon> weapon_ptr;

}
}
}

#endif
