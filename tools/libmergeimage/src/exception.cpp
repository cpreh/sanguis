#include <sanguis/tools/libmergeimage/exception.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/make_message.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::tools::libmergeimage::exception::exception(fcppt::string &&_text)
    : fcppt::exception(std::move(_text))
{
}

sanguis::tools::libmergeimage::exception::exception(exception &&) noexcept = default;

sanguis::tools::libmergeimage::exception::exception(exception const &) = default;

sanguis::tools::libmergeimage::exception &
sanguis::tools::libmergeimage::exception::operator=(exception &&) noexcept = default;

sanguis::tools::libmergeimage::exception &
sanguis::tools::libmergeimage::exception::operator=(exception const &) = default;

sanguis::tools::libmergeimage::exception::~exception() noexcept = default;
