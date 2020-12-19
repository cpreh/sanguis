#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_ATTRIBUTE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_ATTRIBUTE_HPP_INCLUDED

#include <sanguis/server/entities/enemies/attribute_fwd.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{

class attribute
{
public:
	explicit
	attribute(
		fcppt::string &&
	);

	[[nodiscard]]
	fcppt::string const &
	text() const;
private:
	fcppt::string text_;
};

}
}
}
}

#endif
