#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_HPP_INCLUDED

#include "../space_unit.hpp"
#include <sge/signal/object.hpp>
#include <sge/function/object_fwd.hpp>
#include <sge/signal/auto_connection.hpp>
#include <sge/shared_ptr.hpp>

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

	typedef sge::function::object<
		change_callback_fn
	> change_callback;

	property(
		value_type current,
		value_type base);
	explicit property(
		value_type base);

	value_type current() const;
	void current(value_type);

	void add(value_type);

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
	
	sge::signal::auto_connection
	register_max_change_callback(
		change_callback const &);
private:
	void clamp();
	
	value_type
		base_,
		max_linear_,
		max_constant_,
		max_,
		max_old_,
		current_,
		restrict_;
	
	typedef sge::signal::object<
		change_callback_fn
	> change_signal_type;

	typedef sge::shared_ptr<
		change_signal_type
	> signal_ptr;

	signal_ptr 
		change_signal,
		max_change_signal;
};

}
}
}

#endif
