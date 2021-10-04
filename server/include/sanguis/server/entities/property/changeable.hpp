#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGEABLE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGEABLE_HPP_INCLUDED

#include <sanguis/server/entities/property/base.hpp>
#include <sanguis/server/entities/property/change_callback.hpp>
#include <sanguis/server/entities/property/change_signal.hpp>
#include <sanguis/server/entities/property/changeable_fwd.hpp>
#include <sanguis/server/entities/property/initial_fwd.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sanguis::server::entities::property
{

class changeable
:
	public sanguis::server::entities::property::base
{
	FCPPT_NONMOVABLE(
		changeable
	);
public:
	explicit
	changeable(
		sanguis::server::entities::property::initial const &
	);

	~changeable()
	override;

	void
	current(
		sanguis::server::entities::property::value
	);

	[[nodiscard]]
	sanguis::server::entities::property::value
	current() const;

	[[nodiscard]]
	sanguis::server::entities::property::value
	max() const;

	[[nodiscard]]
	fcppt::signal::auto_connection
	register_change_callback(
		sanguis::server::entities::property::change_callback &&
	);

	[[nodiscard]]
	fcppt::signal::auto_connection
	register_max_change_callback(
		sanguis::server::entities::property::change_callback &&
	);
private:
	void
	on_recalc_max(
		sanguis::server::entities::property::value
	)
	override;

	void
	check_current();

	sanguis::server::entities::property::value current_;
	sanguis::server::entities::property::value max_;

	sanguis::server::entities::property::change_signal change_signal_;
	sanguis::server::entities::property::change_signal max_change_signal_;
};

}

#endif
