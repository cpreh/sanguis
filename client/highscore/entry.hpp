#ifndef SANGUIS_CLIENT_HIGHSCORE_ENTRY_HPP_INCLUDED
#define SANGUIS_CLIENT_HIGHSCORE_ENTRY_HPP_INCLUDED

#include "name_container.hpp"
#include "score_type.hpp"

namespace sanguis
{
namespace client
{
namespace highscore
{
class entry
{
public:
	entry();
	entry(
		name_container const &,
		score_type);
	name_container const &names() const;
	score_type score() const;
private:
	name_container names_;
	score_type score_;
};
}
}
}

#endif // SANGUIS_CLIENT_HIGHSCORE_ENTRY_HPP_INCLUDED
