# -*- coding: utf-8 -*-
def about_strjson_dict(self):
    print '===>python object:'
    pobj = {'name':'me'}
    print pobj
    print pobj['name']
    
    print '===>string:'
    str = '{"name":"me"}'
    print str + str[0]
    
    print '===>dict->class'
    jobj = bunch.to_bunch(pobj)
    print jobj
    print jobj.name
    
    print '===>json.dumps(): dict->json'
    dict2json = json.dumps(pobj)
    print dict2json
    print dict2json[0]
    
    print '===>eval():json->dict'
    json2dict = eval(str)
    print json2dict
    print json2dict['name']
    
    print '===>json.loads():json->dict'
    json2dict2 = json.loads(str)
    print json2dict2