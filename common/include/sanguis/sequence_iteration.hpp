#ifndef SANGUIS_SEQUENCE_ITERATION_HPP_INCLUDED
#define SANGUIS_SEQUENCE_ITERATION_HPP_INCLUDED


namespace sanguis
{

template<
	typename Sequence,
	typename UpdateAction
>
void
sequence_iteration(
	Sequence &_sequence,
	UpdateAction const &_update_action
)
{
	for(
		typename Sequence::iterator it(
			_sequence.begin()
		);
		it != _sequence.end();
	)
	{
		if(
			_update_action(
				*it
			)
		)
			it =
				_sequence.erase(
					it
				);
		else
			++it;
	}
}

}

#endif
