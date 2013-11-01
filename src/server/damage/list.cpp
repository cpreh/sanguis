#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/meta.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <fcppt/algorithm/array_init.hpp>
#include <fcppt/cast/enum_to_int.hpp>


sanguis::server::damage::list::list(
	sanguis::server::damage::unit const _value
)
:
	array_(
		fcppt::algorithm::array_init<
			sanguis::server::damage::array
		>(
			_value
		)
	)
{
}

sanguis::server::damage::list::list(
	sanguis::server::damage::meta const &_meta
)
:
	array_(
		fcppt::algorithm::array_init<
			sanguis::server::damage::array
		>(
			sanguis::server::damage::unit(
				0.f
			)
		)
	)
{
	array_[
		fcppt::cast::enum_to_int<
			sanguis::server::damage::array::size_type
		>(
			_meta.type()
		)
	] =
		_meta.value();
}

sanguis::server::damage::list &
sanguis::server::damage::list::operator()(
	sanguis::server::damage::meta const &_meta
)
{
	array_[
		fcppt::cast::enum_to_int<
			sanguis::server::damage::array::size_type
		>(
			_meta.type()
		)
	] =
		_meta.value();

	return *this;
}

sanguis::server::damage::list::
operator sanguis::server::damage::array() const
{
	return array_;
}
