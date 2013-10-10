#include <sanguis/server/entities/property/base.hpp>
#include <sanguis/server/entities/property/constant.hpp>
#include <sanguis/server/entities/property/linear.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::property::base::base(
	sanguis::server::entities::property::value const _base
)
:
	base_(
		_base
	),
	constant_(),
	linear_()
{
}

sanguis::server::entities::property::constant const
sanguis::server::entities::property::base::constant()
{
	return
		constant_;
}

sanguis::server::entities::property::linear const
sanguis::server::entities::property::base::linear()
{
	return
		linear_;
}

void
sanguis::server::entities::property::base::constant(
	sanguis::server::entities::property::constant const &_constant
)
{
	constant_ = _constant;

	this->recalc_max();
}

void
sanguis::server::entities::property::base::linear(
	sanguis::server::entities::property::linear const &_linear
)
{
	linear_ = _linear;

	this->recalc_max();
}

sanguis::server::entities::property::base::~base()
{
}

void
sanguis::server::entities::property::base::recalc_max()
{
	this->on_recalc_max(
		std::max(
			(base_ + constant_.value())
			* linear_.value(),
			fcppt::literal<
				sanguis::server::entities::property::value
			>(
				0
			)
		)
	);
}
