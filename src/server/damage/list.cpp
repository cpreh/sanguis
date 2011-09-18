#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/meta.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

sanguis::server::damage::list::list(
	unit const _value
)
{
	std::fill(
		array_.begin(),
		array_.end(),
		_value
	);
}

sanguis::server::damage::list::list(
	meta const &_meta
)
{
	std::fill(
		array_.begin(),
		array_.end(),
		unit(0)
	);

	array_[_meta.type()] = _meta.value();
}

sanguis::server::damage::list &
sanguis::server::damage::list::operator()(
	meta const &_meta
)
{
	array_[_meta.type()] = _meta.value();

	return *this;
}

sanguis::server::damage::list::
operator sanguis::server::damage::array() const
{
	return array_;
}
