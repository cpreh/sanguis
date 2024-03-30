#include <sanguis/duration.hpp>
#include <sanguis/server/ai/status.hpp>
#include <sanguis/server/ai/tree/basic_sequence.hpp>
#include <sanguis/server/ai/tree/container.hpp>
#include <sanguis/server/ai/tree/priority_sequence.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::ai::tree::priority_sequence::priority_sequence(
    sanguis::server::ai::tree::container &&_children)
    : sanguis::server::ai::tree::basic_sequence(std::move(_children))
{
}

sanguis::server::ai::tree::priority_sequence::~priority_sequence() = default;

sanguis::server::ai::status
sanguis::server::ai::tree::priority_sequence::run(sanguis::duration const _duration)
{
  for (auto const &child : this->get())
  {
    FCPPT_PP_PUSH_WARNING
    FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
    switch (child->run(_duration))
    {
    case sanguis::server::ai::status::failure:
      continue;
    case sanguis::server::ai::status::success:
      return sanguis::server::ai::status::success;
    case sanguis::server::ai::status::running:
      return sanguis::server::ai::status::running;
    }
    FCPPT_PP_POP_WARNING
  }

  return sanguis::server::ai::status::failure;
}
