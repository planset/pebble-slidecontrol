======
README
======
pebbleからkeynoteのページを進めたり戻したりする。

pebble/config.htmlをどこかアクセスできるところにおいて、pebble/src/js/pebble-js-app.jsのconfigUrlを変更して下さい。


pebble
======
::

    cd pebble
    pebble build
    pebble install


server
======
::

    cd server
    virtualenv .env
    source .env/bin/activate
    pip install -r requirements.txt
    python ws_server.py


