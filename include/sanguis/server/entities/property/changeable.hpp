#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGEABLE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGEABLE_HPP_INCLUDED

#include <sanguis/server/entities/property/changeable_fwd.hpp>
#include <sanguis/server/entities/property/base.hpp>
#include <sanguis/server/entities/property/initial_fwd.hpp>
#include <sanguis/server/entities/property/change_callback.hpp>
#include <sanguis/server/entities/property/change_signal.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/noncopyable.hpp>

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
	public property::base
{
	FCPPT_NONCOPYABLE(
		changeable
	);
public:
	explicit changeable(
		initial const &
	);

	changeable(
		value_type base,
		value_type current
	);

	~changeable();

	void
	current(
		value_type
	);

	value_type
	current() const;

	value_type
	max() const;

	fcppt::signal::auto_connection
	register_change_callback(
		change_callback const &
	);

	fcppt::signal::auto_connection
	register_max_change_callback(
		change_callback const &
	);
private:
	void
	on_recalc_max(
		value_type
	);

	void
	check_current();

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
