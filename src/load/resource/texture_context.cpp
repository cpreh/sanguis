#include "texture_context.hpp"
#include "texture_context_impl.hpp"

sanguis::load::resource::texture_context::texture_context()
:
	value_()
{
}

sanguis::load::resource::texture_context::texture_context(
	texture_context_impl_ptr const &_value
)
:
	value_(
		_value
	)
{
}

sanguis::load::resource::texture_context_impl_ptr const
sanguis::load::resource::texture_context::value() const
{
	return value_;
}

sanguis::load::resource::texture_context::~texture_context()
{
}
