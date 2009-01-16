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
	max_linear_(static_cast<value_type>(1)),
	max_constant_(static_cast<value_type>(0)),
	max_(base_),
	current_(base_),
	restrict_(value_max)
{}

sanguis::server::entities::property::property(
	value_type const ncurrent,
	value_type const base_)
:
	base_(base_),
	max_linear_(static_cast<value_type>(1)),
	max_constant_(static_cast<value_type>(0)),
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
	max_linear_(static_cast<value_type>(1)),
	max_constant_(static_cast<value_type>(0)),
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
	
	change_signal(current());
}

void sanguis::server::entities::property::current_to_max()
{
	current(max());
}

void sanguis::server::entities::property::reset()
{
	max_ = base_;	
	max_linear_ = static_cast<value_type>(1);
	max_constant_ = static_cast<value_type>(0);
}

sanguis::server::entities::property::value_type
sanguis::server::entities::property::max() const
{
	return max_;
}

void sanguis::server::entities::property::add_to_max(
	value_type const n)
{
	max_constant_ += n;
}

void sanguis::server::entities::property::multiply_max(
	value_type const factor)
{
	max_linear_ += factor;
}

void sanguis::server::entities::property::max(
	value_type const n)
{
	max_ = n;
}

void sanguis::server::entities::property::restrict(
	value_type const r)
{
	restrict_ = r;
	clamp();
}

void sanguis::server::entities::property::apply()
{
	max_ = (base_ + max_constant_) * max_linear_;
	clamp();
}

void sanguis::server::entities::property::unrestrict()
{
	restrict_ = value_max;
}

sge::signals::connection const 
	sanguis::server::entities::property::register_change_callback(
	change_callback const &cb)
{
	return change_signal.connect(cb);
}

void sanguis::server::entities::property::clamp()
{
	current(current_);
}
