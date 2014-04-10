#ifndef SANGUIS_SEQUENCE_ITERATION_HPP_INCLUDED
#define SANGUIS_SEQUENCE_ITERATION_HPP_INCLUDED


namespace sanguis
{

template<
	typename Sequence,
	typename UpdateAction,
	typename Predicate,
	typename RemoveAction
>
void
sequence_iteration(
	Sequence &_sequence,
	UpdateAction const &_update_action,
	Predicate const &_predicate,
	RemoveAction const &_remove_action
)
{
	for(
		typename Sequence::iterator it(
			_sequence.begin()
		);
		it != _sequence.end();
	)
	{
		_update_action(
			*it
		);

		if(
			_predicate(
				*it
			)
		)
		{
			_remove_action(
				*it
			);

			it =
				_sequence.erase(
					it
				);
		}
		else
			++it;
	}
}

}

#endif
