import sys

class Node(object):

    def __init__(self, prefix='', nodes=None):
        self.prefix = prefix
        if nodes is None:
            self.nodes = []
        else:
            self.nodes = [nodes]

    def Insert(self, iterable):

        for idx, node in enumerate(self.nodes):
            ok, sub = node.commonPrefix(iterable)
            if ok:
                if sub == node.prefix:
                    node.Insert(iterable[len(sub):])
                    return

                node.prefix = node.prefix[len(sub):]
                self.nodes[idx] = Node(prefix=sub, nodes=node)
                return

        self.nodes.append(Node(prefix=iterable))

    def commonPrefix(self, other):

        idx = 0
        # control variables leak their scope remember
        for idx, element in enumerate(self.prefix):
            if idx > len(other)-1:
                break
            if element != other[idx]:
                break
        if idx > 0:
            return True, other[:idx+1]
        return False, None

    def __repr__(self):
        return self.prefix

    def display(self, msg='Prefix Trie: ', level=0):
        print msg + ('\t' * level) + self.prefix
        for node in self.nodes:
            node.display(msg="node: ", level=level+1)
            
if __name__ == '__main__':
    n = Node()

    for line in open(sys.argv[1]):
        n.Insert(line)
