#include <sanguis/client/draw2d/factory/pickup.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/pickup_type.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/load/pickup_name.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>

namespace
{

fcppt::string const
get_texture(
	sanguis::pickup_type::type
);

}

sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::pickup(
	entities::model::parameters const &_param,
	pickup_type::type const _ptype
)
{
	return
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::model::object
			>(
				fcppt::cref(
					_param
				),
				get_texture(
					_ptype
				),
				z_ordering::pickup,
				entities::model::needs_healthbar::no,
				entities::model::decay_option::immediate
			)
		);
}

namespace
{

fcppt::string const
get_texture(
	sanguis::pickup_type::type const _ptype
)
{
	switch(
		_ptype
	)
	{
	case sanguis::pickup_type::monster:
	case sanguis::pickup_type::health:
		return
			sanguis::load::pickup_name(
				_ptype
			);
	case sanguis::pickup_type::weapon:
		throw sanguis::exception(
			FCPPT_TEXT("draw::factory::pickup: weapon pickup cannot be created using pickup!")
		);
	case sanguis::pickup_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE
}

}
