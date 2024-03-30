#include <sanguis/duration.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/idle.hpp>
#include <sanguis/server/ai/status.hpp>
#include <sanguis/server/ai/behavior/base.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/ai/behavior/base_unique_ptr.hpp>
#include <sanguis/server/ai/tree/base.hpp>
#include <sanguis/server/ai/tree/leaf.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::ai::tree::leaf::leaf(sanguis::server::ai::behavior::base_unique_ptr &&_behavior)
    : sanguis::server::ai::tree::base(), behavior_{std::move(_behavior)}, started_{false}
{
}

sanguis::server::ai::tree::leaf::~leaf() = default;

sanguis::server::entities::transfer_result sanguis::server::ai::tree::leaf::transfer()
{
  return behavior_->transfer();
}

sanguis::server::ai::status sanguis::server::ai::tree::leaf::run(sanguis::duration const _duration)
{
  if (!started_)
  {
    started_ = behavior_->start();
  }

  if (!started_)
  {
    return sanguis::server::ai::status::failure;
  }

  sanguis::server::ai::status const result{behavior_->update(_duration)};

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (result)
  {
  case sanguis::server::ai::status::running:
    break;
  case sanguis::server::ai::status::success:
  case sanguis::server::ai::status::failure:
    started_ = false;

    sanguis::server::ai::idle(behavior_->me());

    behavior_->context().clear_path();
  }
  FCPPT_PP_POP_WARNING

  return result;
}
