#include "property.hpp"
#include <algorithm>
#include <limits>

namespace
{

sanguis::server::entities::property::value_type const
value_max(
	std::numeric_limits<
		sanguis::server::entities::property::value_type
	>::max());

}

sanguis::server::entities::property::property()
:
	base_(static_cast<value_type>(0)),
	max_(base_),
	current_(base_),
	restrict_(value_max)
{}

sanguis::server::entities::property::property(
	value_type const ncurrent,
	value_type const base_)
:
	base_(base_),
	max_(base_),
	current_(static_cast<value_type>(0)),
	restrict_(value_max)
{
	current(ncurrent);
}

sanguis::server::entities::property::property(
	value_type const base_)
:
	base_(base_),
	max_(base_),
	current_(base_),
	restrict_(value_max)
{}

sanguis::server::entities::property::value_type
sanguis::server::entities::property::current() const
{
	return current_;
}

void sanguis::server::entities::property::current(
	value_type const c)
{
	current_ = std::min(
		std::min(
			restrict_,
			max()),
		c);
}

void sanguis::server::entities::property::set_current_to_max()
{
	current_ = max();
}

sanguis::server::entities::property::value_type
sanguis::server::entities::property::max() const
{
	return max_;
}

void sanguis::server::entities::property::reset_max_to_base()
{
	max_ = base_;
}

void sanguis::server::entities::property::add_to_max(
	const value_type n)
{
	const value_type old = max();
	max_ += n;
	adjust_current(old);
}

void sanguis::server::entities::property::multiply_max_with_base(
	const value_type factor)
{
	const value_type old = max();
	max_ += base_ * factor;
	adjust_current(old);
}

void sanguis::server::entities::property::max(
	const value_type n)
{
	const value_type old = max();
	max_ = n;
	adjust_current(old);
}

void sanguis::server::entities::property::restrict(
	value_type const r)
{
	restrict_ = r;
	clamp();
}

void sanguis::server::entities::property::unrestrict()
{
	restrict_ = value_max;
}

void sanguis::server::entities::property::adjust_current(
	value_type const old_max)
{
	if(old_max < max())
		current_ += max() - old_max;
	else if(old_max > max())
		clamp();

}

void sanguis::server::entities::property::clamp()
{
	current(current_);
}
