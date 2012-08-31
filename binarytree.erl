-module(binarytree).
-compile(export_all).

%% Registers the async'd Pid with the atom 'root'.
init() ->
    register(root, spawn(binarytree,server,[])).

%% "Constructor" for the server, seeds initial values.
server() ->
    server(nil, nil, nil).
server(Left, Value, Right) ->
    receive
        {add, Data, From} ->
            if  %% Value =:= nil only on the first root node.
                Value =:= nil ->
                    From ! added,
                    server(Left, Data, Right);
                Value > Data ->
                    if  %% Left/Right =:= nil when it's a bare node.
                        %% So we spawn a new node with the Data as
                        %% it's value.
                        Left =:= nil ->
                            From ! added,
                            NewPid = spawn(binarytree, server, [nil, Data, nil]),
                            server(NewPid, Value, Right);
                        true ->
                            Left ! {add, Data, From},
                            server(Left, Value, Right)
                    end;

                true ->
                    if
                        Right =:= nil ->
                            From ! added,
                            NewPid = spawn(binarytree, server, [nil, Data, nil]),
                            server(Left, Value, NewPid);
                        true ->
                            Right ! {add, Data, From},
                            server(Left, Value, Right)
                    end
            end;

        {walk, Who} ->
            %% When we get a call to walk, we recursively
            %% tell sub-nodes to walk as well using the
            %% call to retrieve which will accumulate
            %% the results and then send it back up the
            %% chain.
            L = Left,
            if
                L =:= nil ->
                    LVals = [];
                true ->
                    LVals = retrieve(Left)
            end,
            R = Right,
            if
                R =:= nil ->
                    RVals = [];
                true ->
                    RVals = retrieve(Right)
            end,
            Who ! {val, LVals++[Value]++RVals},
            server(Left, Value, Right)
    end.

%% Kicks off the walk by sending to the root node.
walk()->
    root ! {walk, self()},
    receive
        {val, Values} ->
            Val = Values
    after
        5000 ->
            Val = []
    end,
    Val.

%% Adds data to the tree.
add(Data) ->
    root ! {add, Data, self()},
    receive
        added ->
            ok
    end.

%% Used internally by the binary tree to retrieve sub
%% node's data.
retrieve(Who) ->
    Who ! {walk, self()},
    receive
        {val, Values} ->
            Vals = Values
    end,
    Vals.

addNValues(0) ->
    ok;
addNValues(N) ->
    add(random:uniform(1000)),
    addNValues(N-1).
