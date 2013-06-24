-module(binarytree_app).
-behaviour(application).

%% API.
-export([start/2]).
-export([stop/1]).

%% API.
start(_Type, _Args) ->
    ok.

stop(_State) ->
    ok.
