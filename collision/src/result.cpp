#include <sanguis/collision/result.hpp>
#include <sanguis/collision/speed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::collision::result::result(sanguis::collision::speed _speed) : speed_(std::move(_speed)) {}

sanguis::collision::speed sanguis::collision::result::speed() const { return speed_; }
