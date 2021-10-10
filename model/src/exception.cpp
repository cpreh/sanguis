#include <sanguis/model/exception.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::model::exception::exception(fcppt::string &&_message)
    : fcppt::exception(FCPPT_TEXT("sanguis::model: ") + std::move(_message))
{
}

sanguis::model::exception::exception(exception &&) noexcept = default;

sanguis::model::exception::exception(exception const &) = default;

sanguis::model::exception &sanguis::model::exception::operator=(exception &&) noexcept = default;

sanguis::model::exception &sanguis::model::exception::operator=(exception const &) = default;

sanguis::model::exception::~exception() noexcept = default;
