#ifndef SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED

#include "../../time_type.hpp"
#include "../../messages/types.hpp"
#include "../../weapon_type.hpp"
#include "../insert_callback.hpp"
#include "../send_callback.hpp"
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
		const send_callback &,
		const insert_callback &,
		const weapon_type::type,
		messages::space_unit range,
		time_type base_cooldown);

	virtual void do_attack(
		entity const &from,
		messages::pos_type const& to) = 0;
	
	entity &insert(entity_ptr);
	void send(messages::base *);
	insert_callback get_insert_callback() const;
	send_callback get_send_callback() const;
private:
	bool in_range(
		entity const& from,
		messages::pos_type const& to) const;

	weapon_type::type    type_;
	messages::space_unit range_;
	sge::timer           cooldown_timer;
	send_callback        send_callback_;
	insert_callback      insert_callback_;
};

typedef std::auto_ptr<weapon> weapon_ptr;

}
}
}

#endif
