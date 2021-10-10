#include <sanguis/duration.hpp>
#include <sanguis/server/ai/status.hpp>
#include <sanguis/server/ai/tree/basic_sequence.hpp>
#include <sanguis/server/ai/tree/container.hpp>
#include <sanguis/server/ai/tree/sequence.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <utility>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::ai::tree::sequence::sequence(sanguis::server::ai::tree::container &&_children)
    : sanguis::server::ai::tree::basic_sequence(std::move(_children)), current_{this->get().begin()}
{
}

FCPPT_PP_POP_WARNING

sanguis::server::ai::tree::sequence::~sequence() = default;

sanguis::server::ai::status
sanguis::server::ai::tree::sequence::run(sanguis::duration const _duration)
{
  if (current_ == this->get().end())
  {
    current_ = this->get().begin();

    return sanguis::server::ai::status::success;
  }

  switch ((*current_)->run(_duration))
  {
  case sanguis::server::ai::status::failure:
    current_ = this->get().begin();

    return sanguis::server::ai::status::failure;
  case sanguis::server::ai::status::success:
    current_ = std::next(current_);

    return sanguis::server::ai::status::running;
  case sanguis::server::ai::status::running:
    return sanguis::server::ai::status::running;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
