RELNAME=binarytree
TABLE=blog

all:
	rebar get-deps; rebar compile; relx

run:
	_rel/bin/$(RELNAME) console

clean:
	rm -r _rel ebin/ deps

deps:
	rebar get-deps

docs:
	erl -noshell \
		-eval 'edoc:application($(RELNAME), ".", []), init:stop().'
