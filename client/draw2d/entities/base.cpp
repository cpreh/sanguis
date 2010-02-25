#include "base.hpp"
#include "../log.hpp"
#include <fcppt/log/headers.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/text.hpp>

sanguis::client::draw2d::entities::base::base()
:
	removed_(false),
	refs_(1)
{}

void
sanguis::client::draw2d::entities::base::decay()
{
	if(
		dec_ref()
	)
		on_decay();
	else
		FCPPT_LOG_WARNING(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("decay() called but refcount is ")
				<< refs_
		);
}

void
sanguis::client::draw2d::entities::base::remove()
{
	if(
		dec_ref()
	)
		removed_ = true;
	else
		FCPPT_LOG_WARNING(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("remove() called but refcount is ")
				<< refs_
		);
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

	FCPPT_LOG_WARNING(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("inc_ref(): refs_ is now ")
			<< refs_
	);
}

void
sanguis::client::draw2d::entities::base::on_decay()
{
	removed_ = true;
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
