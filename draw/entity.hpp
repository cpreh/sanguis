#ifndef SANGUIS_DRAW_ENTITY_HPP_INCLUDED
#define SANGUIS_DRAW_ENTITY_HPP_INCLUDED

#include "system_fwd.hpp"
#include "vector2.hpp"
#include "object_fwd.hpp"
#include "../entity_id.hpp"
#include "../weapon_type.hpp"
#include "../time_type.hpp"
#include "../diff_clock.hpp"
#include <sge/time/timer.hpp>
#include <sge/log/fwd.hpp>
#include <sge/sprite/rotation_type.hpp>
#include <sge/sprite/point.hpp>
#include <sge/sprite/dim.hpp>
#include <boost/noncopyable.hpp>
#include <vector>

namespace sanguis
{
namespace draw
{

class environment;

class entity : boost::noncopyable {
public:
	typedef std::vector<
		object
	> sprite_vector;

	virtual void update(time_type);
	entity_id id() const;
	void decay();
	void decay_time(
		time_type);
	virtual bool may_be_removed() const;
	virtual void orientation(sge::sprite::rotation_type) = 0;
	virtual void speed(vector2 const &) = 0;
	virtual void pos(sge::sprite::point const &) = 0;
	virtual void dim(sge::sprite::dim const &) = 0;
	virtual void visible(bool) = 0;
	virtual void health(funit);
	virtual void max_health(funit);
	virtual void weapon(weapon_type::type);
	virtual void start_attacking();
	virtual void stop_attacking();
	virtual void start_reloading();
	virtual void stop_reloading();
	virtual ~entity();
protected:
	entity(
		draw::environment const &,
		entity_id id);
	virtual vector2 const &speed() const = 0;
	virtual funit orientation() const = 0;

	draw::environment const &
	environment() const;

	draw::system &
	system();
private:
	static sge::log::logger &log();

	draw::environment const &env_;
	entity_id               id_;
	diff_clock              diff_clock_;
	sge::time::timer        decay_timer;
};

}
}

#endif
