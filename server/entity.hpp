#ifndef SANGUIS_SERVER_ENTITY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITY_HPP_INCLUDED

#include "../messages/types.hpp"
#include "../entity_id.hpp"
#include "../entity_type.hpp"
#include "ai_type.hpp"
#include "teams.hpp"
#include "weapons/weapon.hpp"
#include <boost/scoped_ptr.hpp>
#include <memory>

namespace sanguis
{
namespace server
{

class entity
{
	public:
	typedef messages::space_unit time_type;

	entity(
		const messages::pos_type &pos,
		const messages::space_unit angle,
		const messages::space_unit direction,
		const messages::space_unit health,
		const messages::space_unit max_health,
		const team::type team,
		const messages::space_unit speed = messages::mu(0));

	entity_id id() const;

	messages::pos_type pos() const;
	void pos(const messages::pos_type);
	messages::space_unit speed() const;
	void speed(const messages::space_unit);
	messages::space_unit angle() const;
	void angle(const messages::space_unit);
	messages::space_unit direction() const;
	void direction(const messages::space_unit);
	messages::space_unit health() const;
	void health(const messages::space_unit);
	messages::space_unit max_health() const;
	void max_health(const messages::space_unit);
	team::type team() const;
	void damage(messages::space_unit);

	bool attacking() const;
	void attacking(const bool);

	bool colliding() const;
	void colliding(const bool);

	// is calculated from the above
	messages::pos_type center() const;
	messages::pos_type abs_speed() const;
	messages::space_unit radius() const;

	virtual void attack(entity &) = 0;
	virtual messages::dim_type dim() const = 0;
	virtual messages::space_unit max_speed() const = 0;
	virtual entity_type::type type() const = 0;
	virtual ai_type::type ai_type() const = 0;
	virtual bool invulnerable() const = 0;
	virtual void update(const time_type);
	virtual ~entity();
	private:
	entity_id id_;
	messages::pos_type pos_;
	messages::space_unit speed_,
	                     angle_,
	                     direction_,
	                     health_,
	                     max_health_;
	team::type team_;
	bool attacking_,
	     colliding_;
	boost::scoped_ptr<weapons::weapon> weapon_;
};

typedef std::auto_ptr<entity> entity_ptr;
}
}

#endif
