# -*- coding: utf-8 -*-
#!/usr/bin/env python
# encoding: UTF-8

__version__ = '0.1'
import sys, os
reload(sys)
sys.setdefaultencoding('utf8')

try:
    import json
except ImportError:
    import simplejson as json
import logging

import web
from web.contrib.template import render_mako

# project external reference extension.
import datetime
import onering
import _py4example
import _py4weibo

import pyparams
from pyparams import *
import mockweibo

urls = (
    '/', 'index',
    '/init', 'init',
    '/apitest', 'apitest',
    '/apitest/getdata', 'getdata',
    '/apitest/getcdata', 'getcdata',
    '/apitest/getfollower', 'getfollower',
    '/apitest/getfollowing', 'getfollowing',
    '/apitest/getweibobyid', 'getweibobyid',
    '/apitest/getweibobytree', 'getweibobytree',
    
    '/sinaweibodemo', 'sinaweibodemo',
    '/sinaweibo_template', 'sinaweibo_template',
    '/sinaweibo_demo', 'sinaweibo_demo',
    '/sinaweibodemo2', 'sinaweibodemo2',
    '/static/(.*)', 'static',
)
render = render_mako(
    directories=['templates'],
    input_encoding='utf8',
    output_encoding='utf8',
)
obj = appargv()

def jsonize(func):
    def _(*a, **kw):
        ret = func(*a, **kw)
        web.header('Content-Type', 'application/json')
        return json.dumps(ret)
    return _
class init:
    @jsonize
    def GET(self):
        url = ('/' + startup_demo) if startup_demo else '/'
        return dict(width=640, height=480, title="新浪微博", url=url, appname="SinaWeibo", icon="/static/onering.ico")
class static:
    def GET(self, filename):
        content = open('static/%s' % filename, 'rb').read()
        content_types = {
            '.js': 'text/javascript',
            '.css': 'text/css',
            '.ico': 'image/x-icon',
        }
        ext = os.path.splitext(filename)[1]
        content_type = content_types.get(ext, 'application/octet-stream')
        web.header('Content-Type', content_type)
        web.header('Content-Length', len(content))
        return content    
class index:        
    def GET(self):
        if obj.refs == 0:
            print '[baiku]start baiku prepare login...'
            _py4weibo.login("13581877736","E10ADC3949BA59ABBE56E057F20F883E");
            print '[baiku]end baiku prepare login!!!'
            obj.refs = 1
        return render.index()
# =====================================================>
# 'apitest' html template
class apitest:
    def GET(self):
        return render.apitest()
class getdata:
    def POST(self):
        return mockweibo.getMessageByTimestamp()
class getcdata:
    def POST(self):
        return _py4example.getdata()
class getfollower:
    def POST(self):
        json = web.input()
        userid = json.userid
        return mockweibo.getFollower(userid)
class getfollowing:
    def POST(self):
        json = web.input()
        userid = json.userid
        return mockweibo.getFollowing(userid)
class getweibobyid:
    def GET(self):
        j_param = web.input()
        msgid = j_param.msgid
        print 'get_weibo_by_id, msgid:' + msgid
        j_weibo = _py4weibo.get_weibo(msgid)
        print j_weibo
        return json.dumps(j_weibo)
class getweibobytree:
    def GET(self):
        print 'get_weibo_by_tree'
        json = web.input()
        print json
        return json
# =====================================================>
# 'sinaweibo' html template# 
class sinaweibo_template:
    def GET(self):
        return render.sinaweibo_template()
class sinaweibo_demo:
    def GET(self):
        return render.sinaweibo_demo()
class sinaweibodemo:
    def GET(self):
        print 'sinaweibodemo'
        #return render.sinaweibodemo(convers=[_conver1,_conver2])
        #j_msgs = _py4weibo.get_weibo_tree("", 2)
        #dict_msgs = json.loads(j_msgs);
        _convers = mockweibo.getWeiboDemoData();
        return render.sinaweibodemo(convers=_convers)
class sinaweibodemo2:
    def GET(self):
        j_msg = _py4weibo.get_weibo("3407911524933786")
        dict_msg = json.loads(j_msg);
        print '[baiku] start:'
        print datetime.datetime.now()
        j_msgs = _py4weibo.get_weibo_tree("", 50)
        print '[baiku] getweibotree:'
        print datetime.datetime.now()
        dict_msgs = json.loads(j_msgs);
        print '[baiku] parse:'
        print datetime.datetime.now()
        html = render.sinaweibodemo2(weibo=dict_msg,weibos=dict_msgs)
        print '[baiku] render:'
        print datetime.datetime.now()
        return html 
# ===========================================================>
if '-v' in sys.argv:
    logging.basicConfig(level=logging.DEBUG)
else:
    logging.basicConfig()

if '--demo' in sys.argv:
    startup_demo = sys.argv[sys.argv.index('--demo')+1]
else:
    startup_demo = None

app = web.application(urls, globals(), autoreload=True)

if __name__ == '__main__':
    onering.register_wsgi_app("pyweibo", app.wsgifunc())
    onering.loop("pyweibo")