from functools import wraps

def set_fun1(func):
    print("set_fun1已被定义")    # 打印用于验证在多个装饰器的情况下，多个装饰器之间的执行顺序

    def call_fun1(*args, **kwargs):
        print("call_fun1执行了")   # 当被装饰函数执行时，会打印
        return func()
    return call_fun1


def set_fun2(func):
    print("set_fun2已被定义")

    def call_fun2(*args, **kwargs):
        print("call_fun2执行了")
        return func()
    return call_fun2

table = {}
def reg(op_tag):
    print(op_tag)
    def _decorate(func):
        table[op_tag] = func
        # @wraps(func)
        def wrapper(a, b):
            if a in table:
                return func(a,b)
            return func(a,b)

        return wrapper

    return _decorate

# 装饰函数
@reg("bb")
@reg("aa")
def test(a, b):
    print('---------')
    print("===:",a, b)
    print("******TTTTT")


print(table["aa"])
print(table["bb"])
test("aa",'y')
test("bb",'y')
print(table)
