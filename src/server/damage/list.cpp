#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/meta.hpp>
#include <sanguis/server/damage/unit.hpp>


namespace
{

sanguis::server::damage::array const
init_array(
	sanguis::server::damage::unit const _value
)
{
	sanguis::server::damage::array const ret =
	{{
		_value,
		_value,
		_value,
		_value,
		_value
	}};

	return ret;
}

}

sanguis::server::damage::list::list(
	unit const _value
)
:
	array_(
		init_array(
			_value
		)
	)
{
}

sanguis::server::damage::list::list(
	meta const &_meta
)
:
	array_(
		init_array(
			damage::unit(
				0.f
			)
		)
	)
{
	array_[
		_meta.type()
	] = _meta.value();
}

sanguis::server::damage::list &
sanguis::server::damage::list::operator()(
	meta const &_meta
)
{
	array_[
		_meta.type()
	] = _meta.value();

	return *this;
}

sanguis::server::damage::list::
operator sanguis::server::damage::array() const
{
	return array_;
}
