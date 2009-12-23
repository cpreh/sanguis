#include "entity.hpp"
#include "log.hpp"
#include "environment.hpp"
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/text.hpp>
#include <sge/time/second_f.hpp>
#include <sge/time/resolution.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

sanguis::entity_id
sanguis::draw::entity::id() const
{
	return id_;
}

void sanguis::draw::entity::decay()
{
	may_be_removed_ = true;
	on_decay();
}

bool sanguis::draw::entity::may_be_removed() const
{
	return may_be_removed_;
}

sanguis::draw::remove_action::type
sanguis::draw::entity::remove_action() const
{
	return remove_action::remove;
}

void sanguis::draw::entity::on_remove()
{}

void sanguis::draw::entity::orientation(
	sprite::rotation_type
)
{
	SGE_LOG_WARNING(
		log(),
		fcppt::log::_ << FCPPT_TEXT("Invalid orientation call!"));
}

void sanguis::draw::entity::speed(vector2 const &)
{
	SGE_LOG_WARNING(
		log(),
		fcppt::log::_ << FCPPT_TEXT("Invalid speed call!"));
}

void sanguis::draw::entity::pos(sprite::point const &)
{
	SGE_LOG_WARNING(
		log(),
		fcppt::log::_ << FCPPT_TEXT("Invalid pos call!"));
}

void sanguis::draw::entity::dim(sprite::dim const &)
{
	SGE_LOG_WARNING(
		log(),
		fcppt::log::_ << FCPPT_TEXT("Invalid dim call!"));
}

void sanguis::draw::entity::visible(bool)
{
	SGE_LOG_WARNING(
		log(),
		fcppt::log::_ << FCPPT_TEXT("Invalid visible call!"));
}

void sanguis::draw::entity::health(funit)
{
	SGE_LOG_WARNING(
		log(),
		fcppt::log::_ << FCPPT_TEXT("Invalid health call!"));
}

void sanguis::draw::entity::max_health(funit)
{
	SGE_LOG_WARNING(
		log(),
		fcppt::log::_ << FCPPT_TEXT("Invalid max_health call!"));
}

void sanguis::draw::entity::weapon(weapon_type::type)
{
	SGE_LOG_WARNING(
		log(),
		fcppt::log::_ << FCPPT_TEXT("got a weapon message that can't have a weapon!"));
}

void sanguis::draw::entity::start_attacking()
{
	SGE_LOG_WARNING(
		log(),
		fcppt::log::_ << FCPPT_TEXT("got a start attacking message!"));
}

void sanguis::draw::entity::stop_attacking()
{
	SGE_LOG_WARNING(
		log(),
		fcppt::log::_ << FCPPT_TEXT("got a stop attacking message!"));
}

void sanguis::draw::entity::start_reloading()
{
	SGE_LOG_WARNING(
		log(),
		fcppt::log::_ << FCPPT_TEXT("got a start reloading message!"));
}

void sanguis::draw::entity::stop_reloading()
{
	SGE_LOG_WARNING(
		log(),
		fcppt::log::_ << FCPPT_TEXT("got a stop reloading message!"));
}

void
sanguis::draw::entity::transfer(
	sprite::normal::system &
)
{
	SGE_LOG_WARNING(
		log(),
		fcppt::log::_ << FCPPT_TEXT("Invalid transfer!"));
}

sanguis::draw::entity::~entity()
{}

sanguis::draw::entity::entity(
	draw::environment const &env_,
	entity_id const id_)
:
	env_(env_),
	id_(id_),
	may_be_removed_(false)
{}

sanguis::draw::vector2 const
sanguis::draw::entity::speed() const
{
	SGE_LOG_WARNING(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("Invalid speed getter!"));
	return vector2::null();
}

sanguis::draw::funit
sanguis::draw::entity::orientation() const
{
	SGE_LOG_WARNING(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("Invalid orientation getter!"));
	return static_cast<funit>(0);
}

sanguis::draw::environment const &
sanguis::draw::entity::environment() const
{
	return env_;
}

void sanguis::draw::entity::on_decay()
{}

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
