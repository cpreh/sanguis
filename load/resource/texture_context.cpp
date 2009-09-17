#include "texture_context.hpp"
#include "texture_context_impl.hpp"
#include <sge/cout.hpp>

sanguis::load::resource::texture_context::texture_context()
:
	value_()
{
}

sanguis::load::resource::texture_context::texture_context(
	texture_context_impl_ptr const &_value)
:
	value_(	
		_value)
{
	sge::cout << "created a new texture_context, reviving sprite\n";
	value_->revive();
}

sanguis::load::resource::texture_context_impl_ptr const sanguis::load::resource::texture_context::value() const
{
	return value_;
}

sanguis::load::resource::texture_context::~texture_context()
{
	if (!value_)
		return;
	sge::cout << "in destructor, use count is " << value_.use_count() << "\n";
	if (value_.use_count() == 2)
	{
		sge::cout << "killing\n";
		value_->kill();
	}
}
