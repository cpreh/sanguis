#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGEABLE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGEABLE_HPP_INCLUDED

#include <sanguis/server/entities/property/base.hpp>
#include <sanguis/server/entities/property/changeable_fwd.hpp>
#include <sanguis/server/entities/property/change_callback.hpp>
#include <sanguis/server/entities/property/change_signal.hpp>
#include <sanguis/server/entities/property/initial_fwd.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>
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
	public sanguis::server::entities::property::base
{
	FCPPT_NONCOPYABLE(
		changeable
	);
public:
	explicit
	changeable(
		sanguis::server::entities::property::initial const &
	);

	~changeable();

	void
	current(
		sanguis::server::entities::property::value
	);

	sanguis::server::entities::property::value
	current() const;

	sanguis::server::entities::property::value
	max() const;

	fcppt::signal::auto_connection
	register_change_callback(
		sanguis::server::entities::property::change_callback const &
	);

	fcppt::signal::auto_connection
	register_max_change_callback(
		sanguis::server::entities::property::change_callback const &
	);
private:
	void
	on_recalc_max(
		sanguis::server::entities::property::value
	);

	void
	check_current();

	sanguis::server::entities::property::value
		current_,
		max_;

	sanguis::server::entities::property::change_signal
		change_signal_,
		max_change_signal_;
};

}
}
}
}

#endif
