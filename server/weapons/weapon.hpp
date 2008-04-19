#ifndef SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED

#include "../../time_type.hpp"
#include "../../messages/types.hpp"
#include <sge/timer.hpp>
#include <boost/shared_ptr.hpp>

namespace sanguis
{
namespace server
{

class entity;

namespace weapons
{

class weapon {
public:
	messages::space_unit range() const;
	bool attack(
		entity const &from,
		messages::pos_type const& to);
protected:
	weapon(
		messages::space_unit range,
		time_type base_cooldown);

	virtual void do_attack(
		entity const &from,
		messages::pos_type const& to) = 0;
private:
	bool in_range(
		entity const& from,
		messages::pos_type const& to) const;

	messages::space_unit range_;
	sge::timer           cooldown_timer;
};

typedef boost::shared_ptr<weapon> weapon_ptr;

}
}
}

#endif
