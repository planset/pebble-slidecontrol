from __future__ import print_function
import os

import tornado.httpserver
import tornado.ioloop
import tornado.web
import tornado.websocket

from tornado.options import define, options, parse_command_line

define("port", default=8001, help="run on the given port", type=int)


class ControlSlideSocket(tornado.websocket.WebSocketHandler):
    def open(self):
        print('open')

    def check_origin(self, origin):
        return True

    def on_message(self, message):
        print('command = ' + message)
        if message == '0':
            os.system('osascript bin/back.scpt')
        elif message == '1':
            os.system('osascript bin/next.scpt')
        else:
            print('?')

    def on_close(self):
        print('close')


def main():
    parse_command_line()
    app = tornado.web.Application([
        (r"/", ControlSlideSocket)
        ])
    app.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()

if __name__ == "__main__":
    main()
    
