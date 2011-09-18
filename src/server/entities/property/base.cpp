#include <sanguis/server/entities/property/base.hpp>

sanguis::server::entities::property::base::base(
	value const _base
)
:
	base_(_base)
{}

sanguis::server::entities::property::base::constant_type const
sanguis::server::entities::property::base::constant()
{
	return constant_;
}

sanguis::server::entities::property::base::linear_type const
sanguis::server::entities::property::base::linear()
{
	return linear_;
}

void
sanguis::server::entities::property::base::constant(
	constant_type const &_constant
)
{
	constant_ = _constant;

	recalc_max();
}

void
sanguis::server::entities::property::base::linear(
	linear_type const &_linear
)
{
	linear_ = _linear;

	recalc_max();
}

sanguis::server::entities::property::base::~base()
{}

void
sanguis::server::entities::property::base::recalc_max()
{
	this->on_recalc_max(
		(base_ + constant_.value())
		* linear_.value()
	);
}
