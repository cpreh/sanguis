#ifndef SANGUIS_LOAD_SOUND_COLLECTION_HPP_INCLUDED
#define SANGUIS_LOAD_SOUND_COLLECTION_HPP_INCLUDED

#include "sound_container.hpp"
#include "probability_type.hpp"

namespace sanguis
{
namespace load
{

class sound_collection {
public:
	sound_collection(
		sound_container const &,
		probability_type probability);

	sound_container const &sounds() const;
	probability_type probability() const;
private:
	sound_container  sounds_;
	probability_type probability_;
};

}
}

#endif
