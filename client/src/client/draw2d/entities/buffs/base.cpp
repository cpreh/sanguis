#include <sanguis/client/draw2d/entities/buffs/base.hpp>
#include <sanguis/client/draw2d/entities/model/object_fwd.hpp>
#include <fcppt/assert/pre.hpp>


sanguis::client::draw2d::entities::buffs::base::base()
:
	counter_(
		1U
	)
{
}

sanguis::client::draw2d::entities::buffs::base::~base()
= default;

void
sanguis::client::draw2d::entities::buffs::base::apply(
	sanguis::client::draw2d::entities::model::object &
)
{
}

void
sanguis::client::draw2d::entities::buffs::base::remove(
	sanguis::client::draw2d::entities::model::object &
)
{
}

void
sanguis::client::draw2d::entities::buffs::base::update(
	sanguis::client::draw2d::entities::model::object const &
)
{
}

void
sanguis::client::draw2d::entities::buffs::base::increment()
{
	++counter_;
}

bool
sanguis::client::draw2d::entities::buffs::base::decrement()
{
	FCPPT_ASSERT_PRE(
		counter_ != 0U
	);

	return
		--counter_
		==
		0U;
}
