class Node(object):

    def __init__(self, prefix='', left=None, right=None, nodes=None):
        self.prefix = prefix
        self.left = left
        self.right = right
        if nodes is None:
            self.nodes = []
        else:
            self.nodes = [nodes]

    def Insert(self, iterable):

        for node in self.nodes:
            ok, sub = self.commonPrefix(iterable)
            if ok:
                if sub == node.prefix:
                    node.Insert(iterable[len(sub):])
                    return
                node.prefix = node.prefix[len(sub):]
                node = Node(prefix=sub,nodes=node)
                node.Insert(iterable[len(sub):])
                return

        self.nodes.append(Node(prefix=iterable))

    def commonPrefix(self, other):

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
    n = Node(prefix="some")
    n.Insert("tits")
    n.Insert("something")
    n.Insert("someone")
    
    n.display()
