-module(problem6).
-compile(export_all).

pow(M, Times) ->
    pow(M, Times, 1).
pow(_M, 0, Sum) ->
    Sum;
pow(M, Times, Sum) ->
    pow(M, Times-1, Sum * M).

calculate() ->
    calculate(1, 0, 0).
calculate(101, SumA, SumB) ->
    pow(SumB, 2) - SumA;
calculate(N, SumA, SumB) ->
    calculate(N+1, SumA + pow(N, 2), SumB + N).
