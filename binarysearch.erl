-module(binarysearch).
-compile(export_all).

tail(List) ->
    hd(lists:reverse(List)).

search(For, In) when length(In) =:= 1 ->
    if 
        hd(In) =:= For ->
            0;
        true ->
            -1
    end;
search(For, In) when hd(In) =:= For ->
    0;
search(_For, In) when length(In) =:= 0 ->
    -1;
search(For, In) ->
    PosTail = tail(In),
    if 
        PosTail =:= For ->
            length(In) - 1;
        true ->
            search(For, In, 0, length(In))
    end.
search(For, In, LBound, UBound) when UBound - LBound =:= 1 ->
    if 
        hd(In) =:= For ->
            LBound - 1;
        hd(tl(In)) =:= For ->
            UBound;
        true ->
            -1
    end;
search(For, In, LBound, UBound) ->
    Mid = erlang:trunc((LBound + UBound) / 2),
    io:format(Mid),
    Curr = check_mid(Mid, In),
    io:format("LBound => ~p~nUBound => ~p~n", [LBound, UBound]),
    if
        Curr =:= not_found ->
            -1;
        Curr > For ->
            search(For, In, LBound, Mid);
        Curr < For ->
            search(For, In, Mid, UBound);
        true ->
            Mid - 1
    end.

check_mid(0, _List) ->
    not_found;
check_mid(N, List) ->
    lists:nth(N, List).

assert_equal(Expr1, Expr2) ->
    true = Expr1 =:= Expr2.

do_tests() ->
    assert_equal(-1, search(3, [])),
    io:format("Test ~p passed~n",[1]),
    assert_equal(-1, search(3, [1])),
    io:format("Test ~p passed~n",[2]),
    assert_equal(0,  search(1, [1])),
    io:format("Test ~p passed~n",[3]),
    assert_equal(0,  search(1, [1, 3, 5])),
    io:format("Test ~p passed~n",[4]),
    assert_equal(1,  search(3, [1, 3, 5])),
    io:format("Test ~p passed~n",[5]),
    assert_equal(2,  search(5, [1, 3, 5])),
    io:format("Test ~p passed~n",[6]),
    assert_equal(-1, search(0, [1, 3, 5])),
    io:format("Test ~p passed~n",[7]),
    assert_equal(-1, search(2, [1, 3, 5])),
    io:format("Test ~p passed~n",[8]),
    assert_equal(-1, search(4, [1, 3, 5])),
    io:format("Test ~p passed~n",[9]),
    assert_equal(-1, search(6, [1, 3, 5])),
    io:format("Test ~p passed~n",[10]),
    assert_equal(0,  search(1, [1, 3, 5, 7])),
    io:format("Test ~p passed~n",[11]),
    assert_equal(1,  search(3, [1, 3, 5, 7])),
    io:format("Test ~p passed~n",[12]),
    assert_equal(2,  search(5, [1, 3, 5, 7])),
    io:format("Test ~p passed~n",[13]),
    assert_equal(3,  search(7, [1, 3, 5, 7])),
    io:format("Test ~p passed~n",[14]),
    assert_equal(-1, search(0, [1, 3, 5, 7])),
    io:format("Test ~p passed~n",[15]),
    assert_equal(-1, search(2, [1, 3, 5, 7])),
    io:format("Test ~p passed~n",[16]),
    assert_equal(-1, search(4, [1, 3, 5, 7])),
    io:format("Test ~p passed~n",[17]),
    assert_equal(-1, search(6, [1, 3, 5, 7])),
    io:format("Test ~p passed~n",[18]),
    assert_equal(-1, search(8, [1, 3, 5, 7])),
    io:format("Test ~p passed~n",[19]),
    search(250005, lists:seq(0,500000)).
