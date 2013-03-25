# -*- coding: utf-8 -*-

class Bunch(dict):
    def __init__(self, d):
        dict.__init__(self, d)
        self.__dict__.update(d)

# FIXED:
# only convert json object, not convert json array.
# i.e:
# {'content':{'body':'a message text', 'content_type':'self'}}
# not like this:
# {'contents':[{'body':'a message text', 'content_type':'self'}]}        
def to_bunch(d):
    r={}
    for k, v in d.items():
        if isinstance(v, dict):
            v = to_bunch(v)
        r[k] = v
    return Bunch(r)