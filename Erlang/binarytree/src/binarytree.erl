%%%-------------------------------------------------------------------
%%% @author  <>
%%% @copyright (C) 2013,
%%% @doc
%%%
%%% @end
%%% Created : 24 Jun 2013 by  <>
%%%-------------------------------------------------------------------
-module(binarytree).

-behaviour(gen_server).

%% API
-export([start_link/0, walk/0, add/1, addNValues/1, addValues/1, testforn/1]).

%% gen_server callbacks
-export([init/1, handle_call/3, handle_cast/2, handle_info/2,
         terminate/2, code_change/3]).

-define(SERVER, ?MODULE).

-record(state, {left = nil, value = nil, right = nil}).

%%%===================================================================
%%% API
%%%===================================================================

%%--------------------------------------------------------------------
%% @doc
%% Starts the server
%%
%% @spec start_link() -> {ok, Pid} | ignore | {error, Error}
%% @end
%%--------------------------------------------------------------------
start_link() ->
    Resp = gen_server:start_link({local, ?SERVER}, ?MODULE, [], []),
    Resp.


%%%===================================================================
%%% gen_server callbacks
%%%===================================================================

%%--------------------------------------------------------------------
%% @private
%% @doc
%% Initializes the server
%%
%% @spec init(Args) -> {ok, State} |
%%                     {ok, State, Timeout} |
%%                     ignore |
%%                     {stop, Reason}
%% @end
%%--------------------------------------------------------------------
init([]) ->
    {ok, #state{left=nil, value=nil, right=nil}};
init([Left, Value, Right]) ->
    {ok, #state{left=Left, value=Value, right=Right}}.

%% @doc
%% When we get a call to add some data to the binary tree, we do so by
%% spawning a new gen_server to hold the data and the relevant sibling
%% pids. This is done by holding a reference to Pids which hold a
%% lesser value (Left) and a reference to the pid which hold a higher
%% value (Right).
%% @spec handle_call({add, Data::term()}, _From::pid(), State::record()) -> added
handle_call({add, Data}, _From, State) ->
    if
        State#state.value =:= nil ->
            {reply, added, State#state{value=Data}};
        State#state.value > Data ->
            if  %% Left/Right =:= nil when it's a bare node.
                %% So we spawn a new node with the Data as
                %% it's value.
                State#state.left =:= nil ->
                    {ok, NewPid} = gen_server:start_link(?MODULE, [nil, Data, nil], []),
                    {reply, added, State#state{left=NewPid}};
                true ->
                    gen_server:call(State#state.left, {add, Data}),
                    {reply, added, State}
            end;
        true ->
            if
                State#state.right =:= nil ->
                    {ok, NewPid} = gen_server:start_link(?MODULE, [nil, Data, nil], []),
                    {reply, added, State#state{right=NewPid}};
                true ->
                    gen_server:call(State#state.right, {add, Data}),
                    {reply, added, State}
            end
    end;

%% @doc
%% When we get a call to walk, we recursively tell sub-nodes to walk
%% as well using the call to retrieve which will accumulate the
%% results and then send it back up the chain.
%% @spec handle_call(walk, _From::pid(), State::record()) -> [term()]
handle_call(walk, _From, State) ->
    F = fun(Who) ->
            case Who of
                nil ->
                    [];
                _Else ->
                    gen_server:call(Who, walk)
            end
        end,
    LVals = F(State#state.left),
    RVals = F(State#state.right),
    Reply = LVals++[State#state.value]++RVals,
    {reply, Reply, State};

handle_call(quit, _From, State) ->
    F = fun(Who) ->
                case Who of
                    nil ->
                        ok;
                    _Else ->
                        gen_server:call(Who, quit)
                end
        end,
    F(State#state.left),
    F(State#state.right),
    {reply, ok, State}.

%%--------------------------------------------------------------------
%% @private
%% @doc
%% Handling cast messages
%%
%% @spec handle_cast(Msg, State) -> {noreply, State} |
%%                                  {noreply, State, Timeout} |
%%                                  {stop, Reason, State}
%% @end
%%--------------------------------------------------------------------
handle_cast(_Msg, State) ->
    {noreply, State}.

%%--------------------------------------------------------------------
%% @private
%% @doc
%% Handling all non call/cast messages
%%
%% @spec handle_info(Info, State) -> {noreply, State} |
%%                                   {noreply, State, Timeout} |
%%                                   {stop, Reason, State}
%% @end
%%--------------------------------------------------------------------
handle_info(_Info, State) ->
    {noreply, State}.

%%--------------------------------------------------------------------
%% @private
%% @doc
%% This function is called by a gen_server when it is about to
%% terminate. It should be the opposite of Module:init/1 and do any
%% necessary cleaning up. When it returns, the gen_server terminates
%% with Reason. The return value is ignored.
%%
%% @spec terminate(Reason, State) -> void()
%% @end
%%--------------------------------------------------------------------
terminate(_Reason, _State) ->
    ok.

%%--------------------------------------------------------------------
%% @private
%% @doc
%% Convert process state when code is changed
%%
%% @spec code_change(OldVsn, State, Extra) -> {ok, NewState}
%% @end
%%--------------------------------------------------------------------
code_change(_OldVsn, State, _Extra) ->
    {ok, State}.

%%%===================================================================
%%% Internal functions
%%%===================================================================

%% Kicks off the walk by sending to the root node.
walk()->
    gen_server:call(?SERVER, walk).

%% Adds data to the tree.
add(Data) ->
    gen_server:call(?SERVER, {add, Data}).

addNValues(0) ->
    ok;
addNValues(N) ->
    add(random:uniform(N)),
    addNValues(N-1).

addValues(0) ->
    add(0);
addValues(N) ->
    add(N),
    addValues(N-1).

testforn(N) ->
    addNValues(N),
    gen_server:call(?SERVER, quit).
