import prefixtrie

p = prefixtrie.PrefixTrie("")
p.insert("something")
p.insert("somethingelse")
p.insert("somethingnew")
p.insert("somethingelsenew")

p.walk()
