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
	value_->revive();
}

sanguis::load::resource::texture_context_impl_ptr const
sanguis::load::resource::texture_context::value() const
{
	return value_;
}

sanguis::load::resource::texture_context::~texture_context()
{
	if (!value_)
		return;

	if (value_.use_count() == 2)
		value_->kill();
}
