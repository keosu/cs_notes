/*eslint-disable block-scoped-var, id-length, no-control-regex, no-magic-numbers, no-prototype-builtins, no-redeclare, no-shadow, no-var, sort-vars*/
(function(global, factory) { /* global define, require, module */

    /* AMD */ if (typeof define === 'function' && define.amd)
        define(["protobufjs/minimal"], factory);

    /* CommonJS */ else if (typeof require === 'function' && typeof module === 'object' && module && module.exports)
        module.exports = factory(require("protobufjs/minimal"));

})(this, function($protobuf) {
    "use strict";

    // Common aliases
    var $Reader = $protobuf.Reader, $Writer = $protobuf.Writer, $util = $protobuf.util;
    
    // Exported root namespace
    var $root = $protobuf.roots["default"] || ($protobuf.roots["default"] = {});
    
    $root.String = (function() {
    
        /**
         * Properties of a String.
         * @exports IString
         * @interface IString
         * @property {string|null} [Val] String Val
         */
    
        /**
         * Constructs a new String.
         * @exports String
         * @classdesc Represents a String.
         * @implements IString
         * @constructor
         * @param {IString=} [properties] Properties to set
         */
        function String(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }
    
        /**
         * String Val.
         * @member {string} Val
         * @memberof String
         * @instance
         */
        String.prototype.Val = "";
    
        /**
         * Creates a new String instance using the specified properties.
         * @function create
         * @memberof String
         * @static
         * @param {IString=} [properties] Properties to set
         * @returns {String} String instance
         */
        String.create = function create(properties) {
            return new String(properties);
        };
    
        /**
         * Encodes the specified String message. Does not implicitly {@link String.verify|verify} messages.
         * @function encode
         * @memberof String
         * @static
         * @param {IString} message String message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        String.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            if (message.Val != null && Object.hasOwnProperty.call(message, "Val"))
                writer.uint32(/* id 1, wireType 2 =*/10).string(message.Val);
            return writer;
        };
    
        /**
         * Encodes the specified String message, length delimited. Does not implicitly {@link String.verify|verify} messages.
         * @function encodeDelimited
         * @memberof String
         * @static
         * @param {IString} message String message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        String.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };
    
        /**
         * Decodes a String message from the specified reader or buffer.
         * @function decode
         * @memberof String
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {String} String
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        String.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.String();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.Val = reader.string();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            return message;
        };
    
        /**
         * Decodes a String message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof String
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {String} String
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        String.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };
    
        /**
         * Verifies a String message.
         * @function verify
         * @memberof String
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        String.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (message.Val != null && message.hasOwnProperty("Val"))
                if (!$util.isString(message.Val))
                    return "Val: string expected";
            return null;
        };
    
        /**
         * Creates a String message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof String
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {String} String
         */
        String.fromObject = function fromObject(object) {
            if (object instanceof $root.String)
                return object;
            var message = new $root.String();
            if (object.Val != null)
                message.Val = String(object.Val);
            return message;
        };
    
        /**
         * Creates a plain object from a String message. Also converts values to other types if specified.
         * @function toObject
         * @memberof String
         * @static
         * @param {String} message String
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        String.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults)
                object.Val = "";
            if (message.Val != null && message.hasOwnProperty("Val"))
                object.Val = message.Val;
            return object;
        };
    
        /**
         * Converts this String to JSON.
         * @function toJSON
         * @memberof String
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        String.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };
    
        return String;
    })();

    return $root;
});
