#include <sanguis/duration.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/time_unit.hpp>

sanguis::duration sanguis::duration_second(sanguis::time_unit const _time)
{
  return sanguis::duration(_time);
}
