#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/parameters.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/attributes/optional_accuracy.hpp>
#include <sanguis/server/weapons/attributes/optional_magazine_size.hpp>


sanguis::server::weapons::parameters::parameters(
	sanguis::random_generator &_random_generator,
	sanguis::weapon_type const _weapon_type,
	sanguis::server::weapons::attributes::optional_accuracy const _accuracy,
	sanguis::server::weapons::range const _range,
	sanguis::server::weapons::attributes::optional_magazine_size const _magazine_size,
	sanguis::server::weapons::backswing_time const _backswing_time,
	sanguis::server::weapons::cast_point const _cast_point,
	sanguis::server::weapons::optional_reload_time const _reload_time
)
:
	random_generator_(
		_random_generator
	),
	weapon_type_{
		_weapon_type
	},
	accuracy_{
		_accuracy
	},
	range_{
		_range
	},
	magazine_size_{
		_magazine_size
	},
	backswing_time_{
		_backswing_time
	},
	cast_point_{
		_cast_point
	},
	reload_time_{
		_reload_time
	}
{
}

sanguis::random_generator &
sanguis::server::weapons::parameters::random_generator() const
{
	return
		random_generator_;
}

sanguis::weapon_type
sanguis::server::weapons::parameters::weapon_type() const
{
	return
		weapon_type_;
}

sanguis::server::weapons::attributes::optional_accuracy
sanguis::server::weapons::parameters::accuracy() const
{
	return
		accuracy_;
}

sanguis::server::weapons::range
sanguis::server::weapons::parameters::range() const
{
	return
		range_;
}

sanguis::server::weapons::attributes::optional_magazine_size
sanguis::server::weapons::parameters::magazine_size() const
{
	return
		magazine_size_;
}

sanguis::server::weapons::backswing_time
sanguis::server::weapons::parameters::backswing_time() const
{
	return
		backswing_time_;
}

sanguis::server::weapons::cast_point
sanguis::server::weapons::parameters::cast_point() const
{
	return
		cast_point_;
}

sanguis::server::weapons::optional_reload_time
sanguis::server::weapons::parameters::reload_time() const
{
	return
		reload_time_;
}
