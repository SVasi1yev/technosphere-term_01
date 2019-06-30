import copy

class FragileDict:
    def __init__(self, data = None):
        if data is not None:
            self._data = copy.deepcopy(data)
        else:
            self._data = {}
        self._lock = True
        
    def __getitem__(self, key):
        if self._lock:
            if key not in self._data:
                raise KeyError()
            return copy.deepcopy(self._data[key])
        else:
            if key not in self._temp_data:
                raise KeyError()
            return self._temp_data[key]
    
    def __setitem__(self, key, value):
        if self._lock:
            raise RuntimeError("Protected state")
        else:
            self._temp_data[key] = value
            
    def __contains__(self, key):
        if self._lock:
            return key in self._data
        else:
            return key in self._temp_data
            
    def __enter__(self):
        self._lock = False
        self._temp_data = copy.deepcopy(self._data)
        return self
    
    def __exit__(self, exc_type, exc_value, traceback):
        if exc_type is not None:
            del self._temp_data
            print("Exception has been suppressed.")
            self._lock = True
            return True
        else:
            self._data = copy.deepcopy(self._temp_data)
            del self._temp_data
            self._lock = True
            return True