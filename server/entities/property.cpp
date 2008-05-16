#include "property.hpp"
#include <algorithm>

sanguis::server::entities::property::property(
	const value_type ncurrent,
	const value_type base_)
	: base_(base_),
	  max_(base_),
	  current_(static_cast<value_type>(0))
{
	current(ncurrent);
}

sanguis::server::entities::property::property(
	const value_type base_)
	: base_(base_),
	  max_(base_),
	  current_(base_)
{}

sanguis::server::entities::property::value_type
sanguis::server::entities::property::current() const
{
	return current_;
}

void sanguis::server::entities::property::current(
	const value_type c)
{
	current_ = std::min(max(), c);
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

void sanguis::server::entities::property::adjust_current(
	const value_type old_max)
{
	if(old_max < max())
		current_ += max() - old_max;
	else if(old_max > max())
		current(current()); // reset current to clamp it
}
