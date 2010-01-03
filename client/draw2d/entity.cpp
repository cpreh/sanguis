#include "entity.hpp"
#include "log.hpp"
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>

bool
sanguis::draw::entity::may_be_removed() const
{
	return may_be_removed_;
}

sanguis::draw::remove_action::type
sanguis::draw::entity::remove_action() const
{
	return remove_action::remove;
}

void
sanguis::draw::entity::on_remove()
{}

sanguis::draw::entity::~entity()
{}

sanguis::draw::entity::entity()
:
	may_be_removed_(false)
{}

sanguis::draw::funit
sanguis::draw::entity::orientation() const
{
	FCPPT_LOG_WARNING(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("Invalid orientation getter!")
	);
	
	return static_cast<funit>(0);
}

fcppt::log::object &
sanguis::draw::entity::log()
{
	static fcppt::log::object log_(
		fcppt::log::parameters::inherited(
			draw::log(),
			FCPPT_TEXT("entity")
		)
	);
	return log_;
}
