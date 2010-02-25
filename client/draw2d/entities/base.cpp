#include "base.hpp"
#include <fcppt/assert.hpp>

sanguis::client::draw2d::entities::base::base()
:
	removed_(false),
	refs_(1)
{}

void
sanguis::client::draw2d::entities::base::decay()
{
	// decay can be overridden so that is_decayed() can be used
	removed_ = true;
}

void
sanguis::client::draw2d::entities::base::remove()
{
	if(
		dec_ref()
	)
		removed_ = true;
}

void
sanguis::client::draw2d::entities::base::on_remove()
{}

bool
sanguis::client::draw2d::entities::base::may_be_removed() const
{
	return
		removed_
		|| is_decayed();
}

sanguis::client::draw2d::entities::base::~base()
{}

void
sanguis::client::draw2d::entities::base::inc_ref()
{
	++refs_;
}

bool
sanguis::client::draw2d::entities::base::dec_ref()
{
	FCPPT_ASSERT(refs_ != 0);

	return --refs_ == 0;
}

bool
sanguis::client::draw2d::entities::base::is_decayed() const
{
	return false;
}
