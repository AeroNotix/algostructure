import sys
import prefixtrie

p = prefixtrie.PrefixTrie("S")

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print "Please supply a file"
        sys.exit(-1)

    fname = open(sys.argv[1], "rb")
    for word in fname:
        p.insert(word)
    print p.walk()
