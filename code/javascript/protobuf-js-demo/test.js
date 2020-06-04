


let fs = require('fs')
let str_pb = require('./protocol/str_pb');


function wt() {
    // serial and write
    let msg = new str_pb.String();
    msg.setVal(" messge , hahah, haha ~~");
    let bytes = msg.serializeBinary();
    fs.writeFile(__dirname + '/save.pb', bytes, (err) => {
        if (err)
            console.error(err);
        else {
            console.log('write ok!!');
            rd();
        }
    });
}

function rd() {
    // read and deserial
    let rdbytes = fs.readFile(__dirname + '/save.pb', null, (err, data) => {
        if (err) {
            console.error(err);
            return;
        }
        console.log('read OK!!');
        let demsg = str_pb.String.deserializeBinary(data);
        console.log(demsg.array[0])
    }); 
}

// wt();

/////////////////////////////////////////

fs.readFile(__dirname + '/save.pb', null, (err, data) => {
    if (err) {
        console.error(err);
        return;
    }

    console.log('read OK!!');
    // use google-protobuf
    let demsg = str_pb.String.deserializeBinary(data);
    console.log(demsg.array[0])

    // use protobufjs json format
    let protobuf = require("protobufjs");
    const root = protobuf.Root.fromJSON(require("./protocol/str.json"));
    let Message = root.lookupType("String");
    let xxmsg = Message.decode(data);
    console.log(xxmsg.Val);

    // use protobufjs js format
    let pb = require('./protocol/str');
    console.log(pb.String)
    let msg222 = pb.String.decode(data)
    console.log(msg222)
 
}); 


            

