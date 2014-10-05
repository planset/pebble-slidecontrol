======
README
======

これは何？
==========
pebbleからkeynoteのページを進めたり戻したりするためのプログラムです。


pebbleの時計のインストール方法
==============================
pebble/config.htmlをどこかアクセスできるところにおいて、pebble/src/js/pebble-js-app.jsのconfigUrlを変更して下さい。
（そのままでもいいですが、http://dkpyn.com/sandbox/pebble/config.htmlが急になるなるかもしれませんので、そこはご了承下さい）

::

    cd pebble
    pebble build
    pebble install


server側
========
kyenoteを起動している端末でpythonプログラムを動かします。

::

    cd server
    virtualenv .env
    source .env/bin/activate
    pip install -r requirements.txt
    python ws_server.py


