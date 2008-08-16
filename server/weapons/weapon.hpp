#ifndef SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED

#include "../../time_type.hpp"
#include "../../messages/types.hpp"
#include "../../messages/base.hpp"
#include "../../weapon_type.hpp"
#include "../../diff_clock.hpp"
#include "../environment.hpp"
#include "../entities/entity_fwd.hpp"
#include <sge/time/timer.hpp>
#include <boost/function.hpp>
#include <memory>

namespace sanguis
{
namespace server
{

namespace weapons
{

class weapon {
public:
	messages::space_unit range() const;
	bool attack(
		entities::entity const &from,
		messages::pos_type const& to);
	weapon_type::type type() const;
	void update(
		time_type);
	virtual ~weapon();
protected:
	weapon(
		const sanguis::server::environment &,
		const weapon_type::type,
		messages::space_unit range,
		time_type base_cooldown,
		time_type cast_point = 0);

	virtual void do_attack(
		entities::entity const &from,
		messages::pos_type const& to) = 0;
	
	entities::entity &insert(entities::auto_ptr);
	void send(
		messages::auto_ptr);
	environment get_environment() const;
private:
	bool in_range(
		entities::entity const& from,
		messages::pos_type const& to) const;

	diff_clock           diff;
	environment          env_;
	weapon_type::type    type_;
	messages::space_unit range_;
	sge::time::timer     cooldown_timer,
	                     cast_point_timer;
};

typedef std::auto_ptr<weapon> weapon_ptr;

}
}
}

#endif
