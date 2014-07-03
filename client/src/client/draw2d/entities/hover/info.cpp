#include <sanguis/client/draw2d/entities/hover/info.hpp>
#include <sanguis/client/draw2d/entities/hover/variant.hpp>


sanguis::client::draw2d::entities::hover::info::info(
	sanguis::client::draw2d::entities::hover::variant const &_impl
)
:
	impl_{
		_impl
	}
{
}

sanguis::client::draw2d::entities::hover::variant const &
sanguis::client::draw2d::entities::hover::info::get() const
{
	return
		impl_;
}
