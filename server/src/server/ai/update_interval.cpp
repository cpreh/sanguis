#include <sanguis/duration.hpp>
#include <sanguis/server/ai/update_interval.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>

sanguis::duration sanguis::server::ai::update_interval()
{
  return std::chrono::duration_cast<sanguis::duration>(std::chrono::milliseconds(
      500 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      ));
}
