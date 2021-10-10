#include <sanguis/server/entities/enemies/attribute.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::entities::enemies::attribute::attribute(fcppt::string &&_text)
    : text_(std::move(_text))
{
}

fcppt::string const &sanguis::server::entities::enemies::attribute::text() const { return text_; }
