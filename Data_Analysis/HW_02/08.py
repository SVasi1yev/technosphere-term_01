from collections import deque


class BinarySearchTree:
    def __init__(self, root_value=None):
        self.root = [root_value, None, None]
        
    def append(self, value):
        if self.root[0] is None:
            self.root[0] = value
        else:
            self.__append(self.root, value)
        
    def __append(self, root, value):
        if (value > root[0]):
            if (root[2] is None):
                root[2] = [value, None, None]
            else:
                self.__append(root[2], value)
        else:
            if (root[1] is None):
                root[1] = [value, None, None]
            else:
                self.__append(root[1], value)
                
    def __contains__(self, value):
        if self.root[0] is None:
            return False
        if value == self.root[0]:
            return True
        elif value > self.root[0]:
            if self.root[2] is None:
                return False
            else:
                return self.__contains(self.root[2], value)
        else:
            if self.root[1] is None:
                return False
            else:
                return self.__contains(self.root[1], value)
        
    def __contains(self, root, value):
        if value == root[0]:
            return True
        elif value > root[0]:
            if root[2] is None:
                return False
            else:
                return self.__contains(root[2], value)
        else:
            if root[1] is None:
                return False
            else:
                return self.__contains(root[1], value)
            
    def __iter__(self):
        self.d = deque()
        if not (self.root[0] is None):
            self.d.append(self.root)
        return self
    
    def __next__(self):
        if self.d:
            temp = self.d.popleft()
            if not (temp[1] is None):
                self.d.append(temp[1])
            if not (temp[2] is None):
                self.d.append(temp[2])
            return temp[0]
        else:
            raise StopIteration()