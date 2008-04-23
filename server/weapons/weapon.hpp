#ifndef SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED

#include "../../time_type.hpp"
#include "../../messages/types.hpp"
#include "../insert_callback.hpp"
#include "../send_callback.hpp"
#include "../entity_fwd.hpp"
#include <sge/timer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

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
	virtual ~weapon();
protected:
	weapon(
		const send_callback &,
		const insert_callback &,
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

	messages::space_unit range_;
	sge::timer           cooldown_timer;
	send_callback        send_callback_;
	insert_callback      insert_callback_;
};

typedef boost::shared_ptr<weapon> weapon_ptr;

}
}
}

#endif
