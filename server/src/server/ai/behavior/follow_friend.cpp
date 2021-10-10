#include <sanguis/duration.hpp>
#include <sanguis/server/add_target_callback.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/remove_target_callback.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/context_ref.hpp>
#include <sanguis/server/ai/go_close_to_target.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/status.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/ai/behavior/follow_friend.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/target.hpp>
#include <sanguis/server/auras/target_kind.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/optional_with_body_ref.hpp>
#include <sanguis/server/entities/same_object.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_body_ref.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <fcppt/const.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>

sanguis::server::ai::behavior::follow_friend::follow_friend(
    sanguis::server::ai::context_ref const _context,
    sanguis::server::ai::sight_range const _sight_range)
    : sanguis::server::ai::behavior::base(_context),
      sight_range_{_sight_range},
      potential_targets_(),
      target_()
{
}

sanguis::server::ai::behavior::follow_friend::~follow_friend() = default;

sanguis::server::entities::transfer_result sanguis::server::ai::behavior::follow_friend::transfer()
{
  return sanguis::server::entities::transfer_result(
      this->me().add_aura(fcppt::unique_ptr_to_base<sanguis::server::auras::aura>(
          fcppt::make_unique_ptr<sanguis::server::auras::target>(
              sanguis::server::radius(sight_range_.get()),
              this->me().team(),
              sanguis::server::auras::target_kind::friend_,
              sanguis::server::add_target_callback{
                  [this](sanguis::server::entities::with_body_ref const _with_body)
                  { this->target_enters(_with_body); }},
              sanguis::server::remove_target_callback{
                  [this](sanguis::server::entities::with_body &_with_body)
                  { this->target_leaves(_with_body); }}))));
}

bool sanguis::server::ai::behavior::follow_friend::start()
{
  return fcppt::optional::maybe(
      this->first_target(),
      fcppt::const_(false),
      [this](fcppt::reference<sanguis::server::entities::with_body> const _target)
      {
        target_ = _target.get().link();

        return true;
      });
}

sanguis::server::ai::status sanguis::server::ai::behavior::follow_friend::update(sanguis::duration)
{
  return fcppt::optional::maybe(
      target_.get(),
      [] { return sanguis::server::ai::status::failure; },
      [this](fcppt::reference<sanguis::server::entities::with_links> const _target)
      {
        return sanguis::server::ai::go_close_to_target(
                   this->context(),
                   sanguis::server::ai::target{_target.get().center()},
                   fcppt::literal<sanguis::server::ai::speed_factor>(1))
                   ? sanguis::server::ai::status::running
                   : sanguis::server::ai::status::failure;
      });
}

void sanguis::server::ai::behavior::follow_friend::target_enters(
    sanguis::server::entities::with_body_ref const _with_body)
{
  FCPPT_ASSERT_ERROR(potential_targets_.insert(_with_body).second);

  target_ = FCPPT_ASSERT_OPTIONAL_ERROR(this->first_target()).get().link();
}

void sanguis::server::ai::behavior::follow_friend::target_leaves(
    sanguis::server::entities::with_body &_with_body)
{
  FCPPT_ASSERT_ERROR(potential_targets_.erase(fcppt::make_ref(_with_body)) == 1U);

  fcppt::optional::maybe_void(
      target_.get(),
      [&_with_body, this](fcppt::reference<sanguis::server::entities::with_links> const _target)
      {
        if (sanguis::server::entities::same_object(_target.get(), _with_body))
        {
          target_ = sanguis::server::entities::auto_weak_link();
        }
      });
}

sanguis::server::entities::optional_with_body_ref
sanguis::server::ai::behavior::follow_friend::first_target() const
{
  return potential_targets_.empty() ? sanguis::server::entities::optional_with_body_ref{}
                                    : sanguis::server::entities::optional_with_body_ref{
                                          fcppt::make_ref(potential_targets_.begin()->get())};
}
