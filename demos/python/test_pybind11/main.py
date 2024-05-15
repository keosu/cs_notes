import CallBack

class UserData:
	def __init__(self):
		self.a=0
		self.b=0
	def print(self):
		print("a=",self.a,"b=",self.b)

def callback(userData):
	userData.a+=1
	userData.b+=1

userData=UserData()
userData.print()

CallBack.test_pycallback(userData,callback)
userData.print()
CallBack.test_pycallback(userData,callback)
userData.print()
