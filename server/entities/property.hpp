#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_HPP_INCLUDED

#include "../space_unit.hpp"
#undef max // TODO: find out where windows.h comes from!
#include <sge/signal/object.hpp>
#include <sge/signal/auto_connection.hpp>
#include <sge/shared_ptr.hpp>
#include <boost/function.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class property {
public:
	typedef space_unit value_type;

	typedef void change_callback_fn(
		value_type const &);

	typedef boost::function<
		change_callback_fn
	> change_callback;

	property();
	property(
		value_type current,
		value_type base);
	property(
		value_type base);

	value_type current() const;
	void current(value_type);

	void current_to_max();

	void reset();

	value_type max() const;

	void add_to_max(value_type);
	void multiply_max(value_type);
	void max(value_type);

	void apply();

	void restrict(
		value_type);
	void unrestrict();

	sge::signal::auto_connection
	register_change_callback(
		change_callback const &);
private:
	void clamp();
	
	value_type const base_;
	value_type
		max_linear_,
		max_constant_,
		max_,
		current_,
		restrict_;
	
	typedef sge::signal::object<
		change_callback_fn
	> change_signal_type;

	sge::shared_ptr<
		change_signal_type
	> change_signal;
};

}
}
}

#endif
