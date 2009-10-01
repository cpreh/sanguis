#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGEABLE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGEABLE_HPP_INCLUDED

#include "changeable_fwd.hpp"
#include "base.hpp"
#include "initial_fwd.hpp"
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

class changeable
:
	public base
{
	SGE_NONCOPYABLE(changeable)
public:
	explicit changeable(
		initial const &
	);

	changeable(
		value_type base_,
		value_type current_
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
	on_recalc_max(
		value_type
	);

	void
	clamp_current();

	value_type
		current_,
		max_;
	
	change_signal
		change_signal_,
		max_change_signal_;
};

}
}
}
}

#endif
