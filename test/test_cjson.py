import json
import cjson


def test_cjson():
    obj = 'hello'
    assert cjson.dumps(obj) == json.dumps(obj)

