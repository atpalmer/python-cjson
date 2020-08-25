import json
import cjson


def test_cjson_str():
    obj = 'hello'
    assert cjson.dumps(obj) == json.dumps(obj)


def test_cjson_int():
    obj = 1
    assert cjson.dumps(obj) == json.dumps(obj)

