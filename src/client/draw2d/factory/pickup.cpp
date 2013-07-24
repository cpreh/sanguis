#include <sanguis/exception.hpp>
#include <sanguis/pickup_type.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/needs_healthbar.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
#include <sanguis/client/draw2d/factory/pickup.hpp>
#include <sanguis/load/pickup_name.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


namespace
{

fcppt::string const
get_texture(
	sanguis::pickup_type
);

}

sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::pickup(
	sanguis::client::draw2d::entities::model::parameters const &_param,
	sanguis::pickup_type const _ptype
)
{
	return
		sanguis::client::draw2d::entities::unique_ptr(
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::entities::model::object
			>(
				_param,
				get_texture(
					_ptype
				),
				sanguis::client::draw2d::entities::order_vector{
					sanguis::client::draw2d::z_ordering::pickup
				},
				sanguis::client::draw2d::entities::model::needs_healthbar::no,
				sanguis::client::draw2d::entities::model::decay_option::immediate
			)
		);
}

namespace
{

fcppt::string const
get_texture(
	sanguis::pickup_type const _ptype
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
	}

	FCPPT_ASSERT_UNREACHABLE;
}

}
