#ifndef SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED

#include "../../time_type.hpp"
#include "../../messages/types.hpp"
#include "../../weapon_type.hpp"
#include "../environment.hpp"
#include "../entity_fwd.hpp"
#include <sge/timer.hpp>
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
		entity const &from,
		messages::pos_type const& to);
	weapon_type::type type() const;
	virtual ~weapon();
protected:
	weapon(
		const environment &,
		const weapon_type::type,
		messages::space_unit range,
		time_type base_cooldown);

	virtual void do_attack(
		entity const &from,
		messages::pos_type const& to) = 0;
	
	entity &insert(entity_ptr);
	void send(messages::base *);
	environment get_environment() const;
private:
	bool in_range(
		entity const& from,
		messages::pos_type const& to) const;

	environment          env_;
	weapon_type::type    type_;
	messages::space_unit range_;
	sge::timer           cooldown_timer;
};

typedef std::auto_ptr<weapon> weapon_ptr;

}
}
}

#endif
