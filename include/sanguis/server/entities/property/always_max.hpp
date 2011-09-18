#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_ALWAYS_MAX_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_ALWAYS_MAX_HPP_INCLUDED

#include <sanguis/server/entities/property/always_max_fwd.hpp>
#include <sanguis/server/entities/property/base.hpp>
#include <sanguis/server/entities/property/change_callback.hpp>
#include <sanguis/server/entities/property/change_signal.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace property
{

class always_max
:
	public property::base
{
	FCPPT_NONCOPYABLE(
		always_max
	);
public:
	explicit always_max(
		value_type
	);

	value_type
	current() const;

	fcppt::signal::auto_connection
	register_change_callback(
		change_callback const &
	);
private:
	void
	on_recalc_max(
		value_type
	);

	value_type current_;

	change_signal change_signal_;
};

}
}
}
}

#endif
