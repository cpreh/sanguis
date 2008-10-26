#ifndef SANGUIS_LOAD_SOUND_COLLECTION_HPP_INCLUDED
#define SANGUIS_LOAD_SOUND_COLLECTION_HPP_INCLUDED

#include "sound_container.hpp"
#include <sge/su.hpp>

namespace sanguis
{
namespace load
{

class sound_collection {
public:
	sound_collection(
		sound_container const &,
		sge::space_unit probability);

	sound_container const &sounds() const;
	sge::space_unit probability() const;
private:
	sound_container sounds_;
	sge::space_unit probability_;
};

}
}

#endif
