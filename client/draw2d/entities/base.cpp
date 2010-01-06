#include "base.hpp"
#include "log.hpp"
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>

sanguis::client::draw2d::entities::base::base()
:
	may_be_removed_(false)
{}

bool
sanguis::client::draw2d::entities::base::may_be_removed() const
{
	return may_be_removed_;
}

sanguis::draw::remove_action::type
sanguis::client::draw2d::entities::base::remove_action() const
{
	return remove_action::remove;
}

void
sanguis::client::draw2d::entities::base::on_remove()
{}

sanguis::client::draw2d::entities::base::~base()
{}

sanguis::draw::funit
sanguis::client::draw2d::entities::base::orientation() const
{
	FCPPT_LOG_WARNING(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("Invalid orientation getter!")
	);
	
	return static_cast<funit>(0);
}
