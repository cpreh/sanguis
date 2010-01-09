#include "base.hpp"
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/dim.hpp>

sanguis::client::draw2d::entities::base::base()
:
	may_be_removed_(false)
{}

void
sanguis::client::draw2d::entities::base::decay()
{}

bool
sanguis::client::draw2d::entities::base::may_be_removed() const
{
	return may_be_removed_;
}

void
sanguis::client::draw2d::entities::base::on_remove()
{}

sanguis::client::draw2d::sprite::point const
sanguis::client::draw2d::entities::base::center() const
{
	return pos() + dim() / 2;
}

sanguis::client::draw2d::entities::base::~base()
{}
