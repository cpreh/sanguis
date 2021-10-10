#include <sanguis/server/weapons/default_ias.hpp>
#include <sanguis/server/weapons/ias.hpp>

sanguis::server::weapons::ias sanguis::server::weapons::default_ias()
{
  return sanguis::server::weapons::ias(1.F);
}
