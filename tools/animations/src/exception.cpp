#include <sanguis/tools/animations/exception.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::tools::animations::exception::exception(fcppt::string &&_text)
    : fcppt::exception(std::move(_text))
{
}

sanguis::tools::animations::exception::exception(exception &&) noexcept = default;

sanguis::tools::animations::exception::exception(exception const &) = default;

sanguis::tools::animations::exception &
sanguis::tools::animations::exception::operator=(exception &&) noexcept = default;

sanguis::tools::animations::exception &
sanguis::tools::animations::exception::operator=(exception const &) = default;

sanguis::tools::animations::exception::~exception() noexcept = default;
