class Cache:
    def __init__(self):
        self.capacity = 0
        self.qnodes = {}

    def get_qnode(self, page_number):
        return self.qnodes.get(page_number, None)

    def set_qnode(self, page_number, node):
        if node is None:
            del self.qnodes[page_number]
        else:
            self.qnodes[page_number] = node
        if len(self.qnodes) > self.capacity:
            raise ValueError("Cache is full!")
