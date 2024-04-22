import zmq

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

while True:
 message = socket.recv()
 print("Received: %s" % message)
 socket.send("I am OK!")