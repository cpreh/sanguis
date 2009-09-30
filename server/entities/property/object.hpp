#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "initial_fwd.hpp"
#include "value.hpp"
#include "constant.hpp"
#include "linear.hpp"
#include "change_callback.hpp"
#include "change_signal.hpp"
#include <sge/signal/auto_connection.hpp>
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace property
{

class object {
	SGE_NONCOPYABLE(object)
public:
	typedef property::value value_type;

	typedef property::constant constant_type;

	typedef property::linear linear_type;

	explicit object(
		initial const &
	);

	object(
		value_type base_,
		value_type current_
	);

	constant_type const
	constant();

	linear_type const
	linear();
	
	void
	constant(
		constant_type const &
	);

	void
	linear(
		linear_type const &
	);

	void
	current(
		value_type
	);

	value_type
	current() const;

	value_type
	max() const;

	sge::signal::auto_connection
	register_change_callback(
		change_callback const &
	);

	sge::signal::auto_connection
	register_max_change_callback(
		change_callback const &
	);
private:
	void
	recalc_max();

	void
	clamp_current();

	value_type
		base_,
		current_,
		max_;
	
	constant_type constant_;
	linear_type linear_;

	change_signal
		change_signal_,
		max_change_signal_;
};

}
}
}
}

#endif
