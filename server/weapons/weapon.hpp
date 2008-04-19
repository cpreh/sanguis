#ifndef SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED

#include "../../time_type.hpp"
#include "../../messages/types.hpp"
#include <sge/timer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace sanguis
{
namespace server
{

class entity;
typedef std::auto_ptr<entity> entity_ptr;

namespace weapons
{

class weapon {
public:
	typedef boost::function<entity & (entity_ptr)> insert_callback;

	messages::space_unit range() const;
	bool attack(
		entity const &from,
		messages::pos_type const& to);
protected:
	weapon(
		messages::space_unit range,
		time_type base_cooldown,
		insert_callback);

	virtual void do_attack(
		entity const &from,
		messages::pos_type const& to) = 0;
	
	entity &insert(entity_ptr);
private:
	bool in_range(
		entity const& from,
		messages::pos_type const& to) const;

	messages::space_unit range_;
	sge::timer           cooldown_timer;
	insert_callback      insert_;
};

typedef boost::shared_ptr<weapon> weapon_ptr;

}
}
}

#endif
