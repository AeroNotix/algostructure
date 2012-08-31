-module(binarytree).
-compile(export_all).

init() ->
    register(root, spawn(binarytree,server,[])).

server() ->
    server(nil, nil, nil).
server(Left, Value, Right) ->
    receive
        {add, Data} ->
            if
                Value =:= nil ->
                    io:format("Valuenil"),
                    server(Left, [Data], Right);
                Value > Data ->
                    if 
                        Left =:= nil ->
                            io:format("Creating left node"),
                            NewPid = spawn(binarytree, server, [nil, [Data], nil]),
                            server(NewPid, Value, Right);
                        true ->
                            io:format("~p~n",[Left]),
                            Left ! {add, Data},
                            server(Left, Value, Right)
                    end;

                Value < Data ->
                    if
                        Right =:= nil ->
                            io:format("Creating right node"),
                            NewPid = spawn(binarytree, server, [nil, [Data], nil]),
                            server(Left, Value, NewPid);
                        true ->
                            Right ! {add, Data},
                            server(Left, Value, Right)
                    end
            end;
        {val, Who} ->
            Who ! Value,
            server(Left, Value, Right);

        {left, Who} ->
            Who ! {val, Value},
            if 
                Left /= nil ->
                    Left ! {left, Who};
                Left =:= nil ->
                    Who ! fin
            end,
            server(Left, Value, Right);

        {right, Who} ->
            Who ! {val, Value},
            io:format("~p~n",[Right]),
            if
                Right /= nil ->
                    Right ! {right, Who};
                Right =:= nil ->
                    Who ! fin
            end,
            server(Left, Value, Right)            
    end.


walk() ->
    Pid = spawn(binarytree, walk, [[], self()]),
    root ! {left, Pid},
    receive
        {fin, Left} ->
            ok
    end,
    root ! {right, Pid},
    receive
        {fin, Right} ->
            ok
    end,
    Left++Right.
        
walk(Values, Who) ->
    receive
        {val, Value} ->
            io:format("~p~n",[Values]),
            walk(Values ++ Value, Who);
        fin ->
            io:format("Finishing accumulating"),
            Who ! {fin, Values}
    end.

add(Data) ->
    root ! {add, Data}.
