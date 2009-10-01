#include "base.hpp"
	
sanguis::server::entities::property::base::base(
	value const base_
)
:
	base_(base_)
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
	constant_type const &nconstant_
)
{
	constant_ = nconstant_;
	
	recalc_max();
}

void
sanguis::server::entities::property::base::linear(
	linear_type const &nlinear_
)
{
	linear_ = nlinear_;

	recalc_max();
}

sanguis::server::entities::property::base::~base()
{}

void
sanguis::server::entities::property::base::recalc_max()
{
	on_recalc_max(
		(base_ + constant_.value())
		* linear_.value()
	);
}
