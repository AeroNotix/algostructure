-module(binarytree_app).
-behaviour(application).

%% API.
-export([start/2]).
-export([stop/1]).

%% API.
start(_Type, _Args) ->
    binarytree_sup:start_link().

stop(_State) ->
    ok.
