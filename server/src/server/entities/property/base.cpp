#include <sanguis/server/entities/property/base.hpp>
#include <sanguis/server/entities/property/constant.hpp>
#include <sanguis/server/entities/property/linear.hpp>
#include <sanguis/server/entities/property/linear_decrease.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::property::constant
sanguis::server::entities::property::base::constant() const
{
	return
		constant_;
}

sanguis::server::entities::property::linear
sanguis::server::entities::property::base::linear() const
{
	return
		linear_;
}

sanguis::server::entities::property::linear_decrease
sanguis::server::entities::property::base::linear_decrease() const
{
	return
		linear_decrease_;
}

void
sanguis::server::entities::property::base::constant(
	sanguis::server::entities::property::constant const &_constant
)
{
	constant_ =
		_constant;

	this->recalc_max();
}

void
sanguis::server::entities::property::base::linear(
	sanguis::server::entities::property::linear const &_linear
)
{
	linear_ =
		_linear;

	this->recalc_max();
}

void
sanguis::server::entities::property::base::linear_decrease(
	sanguis::server::entities::property::linear_decrease const &_linear_decrease
)
{
	linear_decrease_ =
		_linear_decrease;

	this->recalc_max();
}

sanguis::server::entities::property::base::base(
	sanguis::server::entities::property::value const _base
)
:
	base_(
		_base
	),
	constant_(),
	linear_(),
	linear_decrease_()
{
}

sanguis::server::entities::property::base::base(
	base &&
) = default;

sanguis::server::entities::property::base &
sanguis::server::entities::property::base::operator=(
	base &&
) = default;

sanguis::server::entities::property::base::~base()
{
}

void
sanguis::server::entities::property::base::recalc_max()
{
	this->on_recalc_max(
		std::max(
			(
				(
					base_
					+
					constant_.value()
				)
				*
				linear_.value()
			),
			fcppt::literal<
				sanguis::server::entities::property::value
			>(
				0
			)
		)
		*
		linear_decrease_.value()
	);
}
