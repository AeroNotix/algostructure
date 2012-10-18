-module(quicksort).
-compile(export_all).


quicksort([]) ->
    [];
quicksort([H | T]) ->
    quicksort([X || X <- T , X < H]) ++ [H] ++ quicksort([X || X <- T, X >= H]).
