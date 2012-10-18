-module(quicksort).
-compile(export_all).


quicksort([]) ->
    [];
quicksort([H | T]) ->
    io:format("~p~n",[H]),
    quicksort([X || X <- T , X < H]) ++ [H] ++ quicksort([X || X <- T, X >= H]).
