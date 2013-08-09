#include <sanguis/weapon_type.hpp>
#include <sanguis/load/weapon_pickup_name.hpp>
#include <sanguis/load/weapon_pickup_name_visitor.hpp>
#include <fcppt/string.hpp>
#include <fcppt/variant/apply_unary.hpp>


fcppt::string
sanguis::load::weapon_pickup_name(
	sanguis::weapon_type const &_type
)
{
	return
		fcppt::variant::apply_unary(
			sanguis::load::weapon_pickup_name_visitor(),
			_type
		);
}
