# protobuf for javascript 

 
 

## 方法一：google-protobuf
npm install google-protobuf 

```
protoc --js_out=import_style=commonjs,binary:. str.proto
```

```js
    let demsg = str_pb.String.deserializeBinary(data);
    console.log(demsg.array[0])
```

## 方法二：protobufjs 
npm install protobufjs 

使用json格式或者js文件均可

```
pbjs -t static-module str.proto > strpb.js
pbjs -t json str.proto > strpb.json
```


```js
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
 
 ```
